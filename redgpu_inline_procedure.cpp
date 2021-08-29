#include "redgpu_inline_procedure.h"

#include <string.h> // For memcpy
#include <mutex>
#include <map>
#include <new>

typedef struct RedInlineGpuCodeAndProcedureHandles {
  RedHandleGpuCode   gpuCodeVertex;
  RedHandleGpuCode   gpuCodeFragment;
  RedHandleProcedure procedure;
} RedInlineGpuCodeAndProcedureHandles;

typedef struct RedInlineProcedureGlobalMapProcedures {
  std::map<uint64_t, RedInlineGpuCodeAndProcedureHandles> procedures;
} RedInlineProcedureGlobalMapProcedures;

typedef struct RedInlineGpuCodeAndProcedureComputeHandles {
  RedHandleGpuCode   gpuCode;
  RedHandleProcedure procedure;
} RedInlineGpuCodeAndProcedureComputeHandles;

typedef struct RedInlineProcedureGlobalMapComputeProcedures {
  std::map<uint64_t, RedInlineGpuCodeAndProcedureComputeHandles> procedures;
} RedInlineProcedureGlobalMapComputeProcedures;

std::mutex                                                               __REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapMutex;
std::map<RedHandleCalls, RedInlineProcedureGlobalMapProcedures *>        __REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_map;
std::mutex                                                               __REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapComputeMutex;
std::map<RedHandleCalls, RedInlineProcedureGlobalMapComputeProcedures *> __REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapCompute;

REDGPU_DECLSPEC void REDGPU_API redCallSetInlineProcedure(RedHandleCalls calls, uint64_t inlineProcedureUniqueKey, const RedInlineProcedure * inlineProcedure, RedStatuses * outStatuses, const char * optionalFile, int optionalLine, void * optionalUserData) {
  int errorCode = 0;

  RedHandleProcedure                      procedure  = 0;
  RedInlineProcedureGlobalMapProcedures * procedures = 0;
  {
    std::lock_guard<std::mutex> __mapMutexScope(__REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapMutex);
    procedures = __REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_map[calls];
    if (procedures == 0) {
      procedures = new(std::nothrow) RedInlineProcedureGlobalMapProcedures();
      if (procedures == 0) {
        errorCode = -1;
      } else {
        __REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_map[calls] = procedures;
      }
    }
  }
  if (errorCode != 0) {
    goto errorExit;
  }

  {
    RedInlineGpuCodeAndProcedureHandles gpuCodeAndProcedureHandles = procedures->procedures[inlineProcedureUniqueKey];
    if (gpuCodeAndProcedureHandles.procedure == 0) {
      // NOTE(Constantine):
      // Not found, create and assign gpu code and procedure handles then.
      redCreateGpuCode(inlineProcedure->context, inlineProcedure->gpu, inlineProcedure->gpuCodeVertexHandleName, inlineProcedure->gpuCodeVertexIrBytesCount, inlineProcedure->gpuCodeVertexIr, &gpuCodeAndProcedureHandles.gpuCodeVertex, outStatuses, optionalFile, optionalLine, optionalUserData);
      if (gpuCodeAndProcedureHandles.gpuCodeVertex == 0) {
        errorCode = -2;
        goto errorExit;
      }
      if (inlineProcedure->gpuCodeFragmentMainProcedureName == 0 && inlineProcedure->gpuCodeFragmentIr == 0) {
      } else {
        redCreateGpuCode(inlineProcedure->context, inlineProcedure->gpu, inlineProcedure->gpuCodeFragmentHandleName, inlineProcedure->gpuCodeFragmentIrBytesCount, inlineProcedure->gpuCodeFragmentIr, &gpuCodeAndProcedureHandles.gpuCodeFragment, outStatuses, optionalFile, optionalLine, optionalUserData);
        if (gpuCodeAndProcedureHandles.gpuCodeFragment == 0) {
          redDestroyGpuCode(inlineProcedure->context, inlineProcedure->gpu, gpuCodeAndProcedureHandles.gpuCodeVertex, optionalFile, optionalLine, optionalUserData);
          errorCode = -3;
          goto errorExit;
        }
      }
      redCreateProcedure(inlineProcedure->context, inlineProcedure->gpu, inlineProcedure->handleName, 0, inlineProcedure->outputDeclaration, inlineProcedure->procedureParameters, inlineProcedure->gpuCodeVertexMainProcedureName, gpuCodeAndProcedureHandles.gpuCodeVertex, inlineProcedure->gpuCodeFragmentMainProcedureName, gpuCodeAndProcedureHandles.gpuCodeFragment, inlineProcedure->state, inlineProcedure->stateExtension, 0, 0, &gpuCodeAndProcedureHandles.procedure, outStatuses, optionalFile, optionalLine, optionalUserData);
      if (gpuCodeAndProcedureHandles.procedure == 0) {
        redDestroyGpuCode(inlineProcedure->context, inlineProcedure->gpu, gpuCodeAndProcedureHandles.gpuCodeVertex, optionalFile, optionalLine, optionalUserData);
        if (gpuCodeAndProcedureHandles.gpuCodeFragment != 0) {
          redDestroyGpuCode(inlineProcedure->context, inlineProcedure->gpu, gpuCodeAndProcedureHandles.gpuCodeFragment, optionalFile, optionalLine, optionalUserData);
        }
        errorCode = -4;
        goto errorExit;
      }
      procedures->procedures[inlineProcedureUniqueKey] = gpuCodeAndProcedureHandles;
    }
    procedure = gpuCodeAndProcedureHandles.procedure;
  }

  {
    RedCallProceduresAndAddresses callPAs = {};
    redGetCallProceduresAndAddresses(inlineProcedure->context, inlineProcedure->gpu, &callPAs, 0, 0, 0, 0);
    callPAs.redCallSetProcedure(calls, RED_PROCEDURE_TYPE_DRAW, procedure);
  }

goto exit;

errorExit:;

  if (outStatuses != 0) {
    if (outStatuses->statusError == RED_STATUS_SUCCESS) {
      outStatuses->statusError            = RED_STATUS_ERROR_VALIDATION_FAILED;
      outStatuses->statusErrorCode        = 0;
      outStatuses->statusErrorHresult     = 0;
      outStatuses->statusErrorProcedureId = RED_PROCEDURE_ID_UNDEFINED;
      outStatuses->statusErrorFile        = optionalFile;
      outStatuses->statusErrorLine        = optionalLine;
      if (errorCode == -1) {
        char desc[512] = "[redCallSetInlineProcedure] new() fail.";
        memcpy(outStatuses->statusErrorDescription, desc, 512);
      } else if (errorCode == -2) {
        char desc[512] = "[redCallSetInlineProcedure] redCreateGpuCode() vertex fail.";
        memcpy(outStatuses->statusErrorDescription, desc, 512);
      } else if (errorCode == -3) {
        char desc[512] = "[redCallSetInlineProcedure] redCreateGpuCode() fragment fail.";
        memcpy(outStatuses->statusErrorDescription, desc, 512);
      } else if (errorCode == -4) {
        char desc[512] = "[redCallSetInlineProcedure] redCreateProcedure() fail.";
        memcpy(outStatuses->statusErrorDescription, desc, 512);
      }
    }
  }

exit:;

}

REDGPU_DECLSPEC void REDGPU_API redCallSetInlineProcedureCompute(RedHandleCalls calls, uint64_t inlineProcedureUniqueKey, const RedInlineProcedureCompute * inlineProcedure, RedStatuses * outStatuses, const char * optionalFile, int optionalLine, void * optionalUserData) {
  int errorCode = 0;

  RedHandleProcedure                             procedure  = 0;
  RedInlineProcedureGlobalMapComputeProcedures * procedures = 0;
  {
    std::lock_guard<std::mutex> __mapComputeMutexScope(__REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapComputeMutex);
    procedures = __REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapCompute[calls];
    if (procedures == 0) {
      procedures = new(std::nothrow) RedInlineProcedureGlobalMapComputeProcedures();
      if (procedures == 0) {
        errorCode = -1;
      } else {
        __REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapCompute[calls] = procedures;
      }
    }
  }
  if (errorCode != 0) {
    goto errorExit;
  }

  {
    RedInlineGpuCodeAndProcedureComputeHandles gpuCodeAndProcedureHandles = procedures->procedures[inlineProcedureUniqueKey];
    if (gpuCodeAndProcedureHandles.procedure == 0) {
      // NOTE(Constantine):
      // Not found, create and assign gpu code and procedure handles then.
      redCreateGpuCode(inlineProcedure->context, inlineProcedure->gpu, inlineProcedure->gpuCodeHandleName, inlineProcedure->gpuCodeIrBytesCount, inlineProcedure->gpuCodeIr, &gpuCodeAndProcedureHandles.gpuCode, outStatuses, optionalFile, optionalLine, optionalUserData);
      if (gpuCodeAndProcedureHandles.gpuCode == 0) {
        errorCode = -2;
        goto errorExit;
      }
      redCreateProcedureCompute(inlineProcedure->context, inlineProcedure->gpu, inlineProcedure->handleName, 0, inlineProcedure->procedureParameters, inlineProcedure->gpuCodeMainProcedureName, gpuCodeAndProcedureHandles.gpuCode, &gpuCodeAndProcedureHandles.procedure, outStatuses, optionalFile, optionalLine, optionalUserData);
      if (gpuCodeAndProcedureHandles.procedure == 0) {
        redDestroyGpuCode(inlineProcedure->context, inlineProcedure->gpu, gpuCodeAndProcedureHandles.gpuCode, optionalFile, optionalLine, optionalUserData);
        errorCode = -3;
        goto errorExit;
      }
      procedures->procedures[inlineProcedureUniqueKey] = gpuCodeAndProcedureHandles;
    }
    procedure = gpuCodeAndProcedureHandles.procedure;
  }

  {
    RedCallProceduresAndAddresses callPAs = {};
    redGetCallProceduresAndAddresses(inlineProcedure->context, inlineProcedure->gpu, &callPAs, 0, 0, 0, 0);
    callPAs.redCallSetProcedure(calls, RED_PROCEDURE_TYPE_COMPUTE, procedure);
  }

goto exit;

errorExit:;

  if (outStatuses != 0) {
    if (outStatuses->statusError == RED_STATUS_SUCCESS) {
      outStatuses->statusError            = RED_STATUS_ERROR_VALIDATION_FAILED;
      outStatuses->statusErrorCode        = 0;
      outStatuses->statusErrorHresult     = 0;
      outStatuses->statusErrorProcedureId = RED_PROCEDURE_ID_UNDEFINED;
      outStatuses->statusErrorFile        = optionalFile;
      outStatuses->statusErrorLine        = optionalLine;
      if (errorCode == -1) {
        char desc[512] = "[redCallSetInlineProcedureCompute] new() fail.";
        memcpy(outStatuses->statusErrorDescription, desc, 512);
      } else if (errorCode == -2) {
        char desc[512] = "[redCallSetInlineProcedureCompute] redCreateGpuCode() fail.";
        memcpy(outStatuses->statusErrorDescription, desc, 512);
      } else if (errorCode == -3) {
        char desc[512] = "[redCallSetInlineProcedureCompute] redCreateProcedure() fail.";
        memcpy(outStatuses->statusErrorDescription, desc, 512);
      }
    }
  }

exit:;

}

REDGPU_DECLSPEC void REDGPU_API redBeforeDestroyCallsDestroyInlineProcedures(RedContext context, RedHandleGpu gpu, RedHandleCalls calls, const char * optionalFile, int optionalLine, void * optionalUserData) {
  {
    std::lock_guard<std::mutex> __mapMutexScope(__REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapMutex);
    RedInlineProcedureGlobalMapProcedures * procedures = __REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_map[calls];
    if (procedures != 0) {
      for (auto & pair : procedures->procedures) {
        redDestroyGpuCode(context, gpu, pair.second.gpuCodeVertex, optionalFile, optionalLine, optionalUserData);
        if (pair.second.gpuCodeFragment != 0) {
          redDestroyGpuCode(context, gpu, pair.second.gpuCodeFragment, optionalFile, optionalLine, optionalUserData);
        }
        redDestroyProcedure(context, gpu, pair.second.procedure, optionalFile, optionalLine, optionalUserData);
      }
      delete procedures;
      __REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_map[calls] = 0;
    }
  }
  {
    std::lock_guard<std::mutex> __mapComputeMutexScope(__REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapComputeMutex);
    RedInlineProcedureGlobalMapComputeProcedures * procedures = __REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapCompute[calls];
    if (procedures != 0) {
      for (auto & pair : procedures->procedures) {
        redDestroyGpuCode(context, gpu, pair.second.gpuCode, optionalFile, optionalLine, optionalUserData);
        redDestroyProcedure(context, gpu, pair.second.procedure, optionalFile, optionalLine, optionalUserData);
      }
      delete procedures;
      __REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapCompute[calls] = 0;
    }
  }
}
