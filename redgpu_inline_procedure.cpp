#include "redgpu_inline_procedure.h"

#include <string.h> // For memcpy
#include <vector>
#include <string>
#include <mutex>
#include <map>
#include <new>

typedef struct RedInlineContextGpuHandle {
  RedContext   context;
  RedHandleGpu gpu;
  void *       handle;
} RedInlineContextGpuHandle;

typedef struct RedInlineGreenStructDeclaration {
  RedContext                                     context;
  RedHandleGpu                                   gpu;
  std::vector<RedStructDeclarationMember>        structDeclarationMembers;
  std::vector<RedStructDeclarationMemberArrayRO> structDeclarationMembersArrayRO;
  RedBool32                                      procedureParametersHandlesDeclaration;
  RedHandleStructDeclaration                     structDeclaration;
} RedInlineGreenStructDeclaration;

typedef struct RedInlineGpuCodeAndProcedureHandles {
  RedContext         context;
  RedHandleGpu       gpu;
  RedHandleGpuCode   gpuCodeVertex;
  RedHandleGpuCode   gpuCodeFragment;
  RedHandleProcedure procedure;
} RedInlineGpuCodeAndProcedureHandles;

typedef struct RedInlineGpuCodeAndProcedureComputeHandles {
  RedContext         context;
  RedHandleGpu       gpu;
  RedHandleGpuCode   gpuCode;
  RedHandleProcedure procedure;
} RedInlineGpuCodeAndProcedureComputeHandles;

typedef struct RedInlineProcedureGlobalMapProcedures {
  std::map<uint64_t, RedInlineGpuCodeAndProcedureHandles> procedures;
} RedInlineProcedureGlobalMapProcedures;

typedef struct RedInlineProcedureGlobalMapComputeProcedures {
  std::map<uint64_t, RedInlineGpuCodeAndProcedureComputeHandles> procedures;
} RedInlineProcedureGlobalMapComputeProcedures;

std::map<std::string, RedInlineContextGpuHandle>                         __REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapOutputDeclarations;
std::map<std::string, RedInlineGreenStructDeclaration *>                 __REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapGreenStructDeclarations;
std::map<std::string, RedInlineContextGpuHandle>                         __REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapProcedureParameters;
std::map<std::string, RedInlineGpuCodeAndProcedureHandles>               __REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapPrecompiles;
std::map<std::string, RedInlineGpuCodeAndProcedureComputeHandles>        __REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapPrecompilesCompute;
std::mutex                                                               __REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapInlinesMutex;
std::map<RedHandleCalls, RedInlineProcedureGlobalMapProcedures *>        __REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapInlines;
std::mutex                                                               __REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapInlinesComputeMutex;
std::map<RedHandleCalls, RedInlineProcedureGlobalMapComputeProcedures *> __REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapInlinesCompute;

REDGPU_DECLSPEC RedHandleOutputDeclaration REDGPU_API redInlineProcedureMapGetOutputDeclaration(const char * key) {
  std::string k = key;
  return (RedHandleOutputDeclaration)__REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapOutputDeclarations[k].handle;
}

REDGPU_DECLSPEC void REDGPU_API redInlineProcedureMapGetGreenStructDeclaration(const char * key, GreenStructDeclaration * outGreenStructDeclaration) {
  std::string k = key;
  RedInlineGreenStructDeclaration * v = __REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapGreenStructDeclarations[k];
  if (v == 0) {
    GreenStructDeclaration empty = {};
    outGreenStructDeclaration[0] = empty;
    return;
  }
  outGreenStructDeclaration->structDeclarationMembersCount         = (unsigned)v->structDeclarationMembers.size();
  outGreenStructDeclaration->structDeclarationMembers              = v->structDeclarationMembers.data();
  outGreenStructDeclaration->structDeclarationMembersArrayROCount  = (unsigned)v->structDeclarationMembersArrayRO.size();
  outGreenStructDeclaration->structDeclarationMembersArrayRO       = v->structDeclarationMembersArrayRO.data();
  outGreenStructDeclaration->procedureParametersHandlesDeclaration = v->procedureParametersHandlesDeclaration;
  outGreenStructDeclaration->structDeclaration                     = v->structDeclaration;
}

REDGPU_DECLSPEC RedHandleProcedureParameters REDGPU_API redInlineProcedureMapGetProcedureParameters(const char * key) {
  std::string k = key;
  return (RedHandleProcedureParameters)__REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapProcedureParameters[k].handle;
}

REDGPU_DECLSPEC void REDGPU_API redInlineProcedureMapSetOutputDeclaration(const char * key, RedContext context, RedHandleGpu gpu, RedHandleOutputDeclaration outputDeclaration) {
  std::string k = key;
  RedInlineContextGpuHandle v = {};
  v.context = context;
  v.gpu     = gpu;
  v.handle  = (void *)outputDeclaration;
  __REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapOutputDeclarations[k] = v;
}

REDGPU_DECLSPEC void REDGPU_API redInlineProcedureMapSetGreenStructDeclaration(const char * key, RedContext context, RedHandleGpu gpu, const GreenStructDeclaration * greenStructDeclaration) {
  std::string k = key;
  RedInlineGreenStructDeclaration * v = new(std::nothrow) RedInlineGreenStructDeclaration();
  if (v == 0) {
    return;
  }
  v->context = context;
  v->gpu     = gpu;
  v->structDeclarationMembers.resize(greenStructDeclaration->structDeclarationMembersCount);
  for (unsigned i = 0; i < greenStructDeclaration->structDeclarationMembersCount; i += 1) {
    v->structDeclarationMembers[i] = greenStructDeclaration->structDeclarationMembers[i];
    // NOTE(Constantine): Not copying RedStructDeclarationMember::inlineSampler for now.
    v->structDeclarationMembers[i].inlineSampler = 0;
  }
  v->structDeclarationMembersArrayRO.resize(greenStructDeclaration->structDeclarationMembersArrayROCount);
  for (unsigned i = 0; i < greenStructDeclaration->structDeclarationMembersArrayROCount; i += 1) {
    v->structDeclarationMembersArrayRO[i] = greenStructDeclaration->structDeclarationMembersArrayRO[i];
  }
  v->procedureParametersHandlesDeclaration = greenStructDeclaration->procedureParametersHandlesDeclaration;
  v->structDeclaration                     = greenStructDeclaration->structDeclaration;
  __REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapGreenStructDeclarations[k] = v;
}

REDGPU_DECLSPEC void REDGPU_API redInlineProcedureMapSetProcedureParameters(const char * key, RedContext context, RedHandleGpu gpu, RedHandleProcedureParameters procedureParameters) {
  std::string k = key;
  RedInlineContextGpuHandle v = {};
  v.context = context;
  v.gpu     = gpu;
  v.handle  = (void *)procedureParameters;
  __REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapProcedureParameters[k] = v;
}

REDGPU_DECLSPEC void REDGPU_API redCreateInlineProcedurePrecompile(RedContext context, RedHandleGpu gpu, const char * inlineProcedurePrecompileUniqueKey, const RedInlineProcedure * inlineProcedure, RedStatuses * outStatuses, const char * optionalFile, int optionalLine, void * optionalUserData) {
  int errorCode = 0;

  std::string precompileKey = inlineProcedurePrecompileUniqueKey;
  RedInlineGpuCodeAndProcedureHandles gpuCodeAndProcedureHandles = __REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapPrecompiles[precompileKey];
  if (gpuCodeAndProcedureHandles.procedure == 0) {
    gpuCodeAndProcedureHandles.context = context;
    gpuCodeAndProcedureHandles.gpu     = gpu;
    // NOTE(Constantine):
    // Not found, create and assign gpu code and procedure handles then.
    redCreateGpuCode(context, gpu, inlineProcedure->gpuCodeVertexHandleName, inlineProcedure->gpuCodeVertexIrBytesCount, inlineProcedure->gpuCodeVertexIr, &gpuCodeAndProcedureHandles.gpuCodeVertex, outStatuses, optionalFile, optionalLine, optionalUserData);
    if (gpuCodeAndProcedureHandles.gpuCodeVertex == 0) {
      errorCode = -1;
      goto errorExit;
    }
    if (inlineProcedure->gpuCodeFragmentMainProcedureName == 0 && inlineProcedure->gpuCodeFragmentIr == 0) {
    } else {
      redCreateGpuCode(context, gpu, inlineProcedure->gpuCodeFragmentHandleName, inlineProcedure->gpuCodeFragmentIrBytesCount, inlineProcedure->gpuCodeFragmentIr, &gpuCodeAndProcedureHandles.gpuCodeFragment, outStatuses, optionalFile, optionalLine, optionalUserData);
      if (gpuCodeAndProcedureHandles.gpuCodeFragment == 0) {
        redDestroyGpuCode(context, gpu, gpuCodeAndProcedureHandles.gpuCodeVertex, optionalFile, optionalLine, optionalUserData);
        errorCode = -2;
        goto errorExit;
      }
    }
    redCreateProcedure(context, gpu, inlineProcedure->handleName, 0, inlineProcedure->outputDeclaration, inlineProcedure->procedureParameters, inlineProcedure->gpuCodeVertexMainProcedureName, gpuCodeAndProcedureHandles.gpuCodeVertex, inlineProcedure->gpuCodeFragmentMainProcedureName, gpuCodeAndProcedureHandles.gpuCodeFragment, inlineProcedure->state, inlineProcedure->stateExtension, 0, 0, &gpuCodeAndProcedureHandles.procedure, outStatuses, optionalFile, optionalLine, optionalUserData);
    if (gpuCodeAndProcedureHandles.procedure == 0) {
      redDestroyGpuCode(context, gpu, gpuCodeAndProcedureHandles.gpuCodeVertex, optionalFile, optionalLine, optionalUserData);
      if (gpuCodeAndProcedureHandles.gpuCodeFragment != 0) {
        redDestroyGpuCode(context, gpu, gpuCodeAndProcedureHandles.gpuCodeFragment, optionalFile, optionalLine, optionalUserData);
      }
      errorCode = -3;
      goto errorExit;
    }
    __REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapPrecompiles[precompileKey] = gpuCodeAndProcedureHandles;
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
        char desc[512] = "[redCreateInlineProcedurePrecompile] redCreateGpuCode() vertex fail.";
        memcpy(outStatuses->statusErrorDescription, desc, 512);
      } else if (errorCode == -2) {
        char desc[512] = "[redCreateInlineProcedurePrecompile] redCreateGpuCode() fragment fail.";
        memcpy(outStatuses->statusErrorDescription, desc, 512);
      } else if (errorCode == -3) {
        char desc[512] = "[redCreateInlineProcedurePrecompile] redCreateProcedure() fail.";
        memcpy(outStatuses->statusErrorDescription, desc, 512);
      }
    }
  }

exit:;

}

REDGPU_DECLSPEC void REDGPU_API redCreateInlineProcedurePrecompileCompute(RedContext context, RedHandleGpu gpu, const char * inlineProcedurePrecompileUniqueKey, const RedInlineProcedureCompute * inlineProcedure, RedStatuses * outStatuses, const char * optionalFile, int optionalLine, void * optionalUserData) {
  int errorCode = 0;

  std::string precompileKey = inlineProcedurePrecompileUniqueKey;
  RedInlineGpuCodeAndProcedureComputeHandles gpuCodeAndProcedureHandles = __REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapPrecompilesCompute[precompileKey];
  if (gpuCodeAndProcedureHandles.procedure == 0) {
    gpuCodeAndProcedureHandles.context = context;
    gpuCodeAndProcedureHandles.gpu     = gpu;
    // NOTE(Constantine):
    // Not found, create and assign gpu code and procedure handles then.
    redCreateGpuCode(context, gpu, inlineProcedure->gpuCodeHandleName, inlineProcedure->gpuCodeIrBytesCount, inlineProcedure->gpuCodeIr, &gpuCodeAndProcedureHandles.gpuCode, outStatuses, optionalFile, optionalLine, optionalUserData);
    if (gpuCodeAndProcedureHandles.gpuCode == 0) {
      errorCode = -1;
      goto errorExit;
    }
    redCreateProcedureCompute(context, gpu, inlineProcedure->handleName, 0, inlineProcedure->procedureParameters, inlineProcedure->gpuCodeMainProcedureName, gpuCodeAndProcedureHandles.gpuCode, &gpuCodeAndProcedureHandles.procedure, outStatuses, optionalFile, optionalLine, optionalUserData);
    if (gpuCodeAndProcedureHandles.procedure == 0) {
      redDestroyGpuCode(context, gpu, gpuCodeAndProcedureHandles.gpuCode, optionalFile, optionalLine, optionalUserData);
      errorCode = -2;
      goto errorExit;
    }
    __REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapPrecompilesCompute[precompileKey] = gpuCodeAndProcedureHandles;
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
        char desc[512] = "[redCreateInlineProcedurePrecompileCompute] redCreateGpuCode() fail.";
        memcpy(outStatuses->statusErrorDescription, desc, 512);
      } else if (errorCode == -2) {
        char desc[512] = "[redCreateInlineProcedurePrecompileCompute] redCreateProcedure() fail.";
        memcpy(outStatuses->statusErrorDescription, desc, 512);
      }
    }
  }

exit:;

}

REDGPU_DECLSPEC void REDGPU_API redCallSetInlineProcedure(RedHandleCalls calls, RedContext context, RedHandleGpu gpu, const char * inlineProcedurePrecompileKey, uint64_t inlineProcedureUniqueKey, const RedInlineProcedure * inlineProcedure, RedStatuses * outStatuses, const char * optionalFile, int optionalLine, void * optionalUserData) {
  int errorCode = 0;

  RedHandleProcedure                      procedure  = 0;
  RedInlineProcedureGlobalMapProcedures * procedures = 0;

  if (inlineProcedurePrecompileKey != 0) {
    std::string precompileKey = inlineProcedurePrecompileKey;
    RedInlineGpuCodeAndProcedureHandles gpuCodeAndProcedureHandles = __REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapPrecompiles[precompileKey];
    if (gpuCodeAndProcedureHandles.procedure == 0) {
      errorCode = -5;
      goto errorExit;
    }
    procedure = gpuCodeAndProcedureHandles.procedure;
    goto precompile;
  }

  {
    std::lock_guard<std::mutex> __mapMutexScope(__REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapInlinesMutex);
    procedures = __REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapInlines[calls];
    if (procedures == 0) {
      procedures = new(std::nothrow) RedInlineProcedureGlobalMapProcedures();
      if (procedures == 0) {
        errorCode = -1;
      } else {
        __REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapInlines[calls] = procedures;
      }
    }
  }
  if (errorCode != 0) {
    goto errorExit;
  }

  {
    RedInlineGpuCodeAndProcedureHandles gpuCodeAndProcedureHandles = procedures->procedures[inlineProcedureUniqueKey];
    if (gpuCodeAndProcedureHandles.procedure == 0) {
      gpuCodeAndProcedureHandles.context = context;
      gpuCodeAndProcedureHandles.gpu     = gpu;
      // NOTE(Constantine):
      // Not found, create and assign gpu code and procedure handles then.
      redCreateGpuCode(context, gpu, inlineProcedure->gpuCodeVertexHandleName, inlineProcedure->gpuCodeVertexIrBytesCount, inlineProcedure->gpuCodeVertexIr, &gpuCodeAndProcedureHandles.gpuCodeVertex, outStatuses, optionalFile, optionalLine, optionalUserData);
      if (gpuCodeAndProcedureHandles.gpuCodeVertex == 0) {
        errorCode = -2;
        goto errorExit;
      }
      if (inlineProcedure->gpuCodeFragmentMainProcedureName == 0 && inlineProcedure->gpuCodeFragmentIr == 0) {
      } else {
        redCreateGpuCode(context, gpu, inlineProcedure->gpuCodeFragmentHandleName, inlineProcedure->gpuCodeFragmentIrBytesCount, inlineProcedure->gpuCodeFragmentIr, &gpuCodeAndProcedureHandles.gpuCodeFragment, outStatuses, optionalFile, optionalLine, optionalUserData);
        if (gpuCodeAndProcedureHandles.gpuCodeFragment == 0) {
          redDestroyGpuCode(context, gpu, gpuCodeAndProcedureHandles.gpuCodeVertex, optionalFile, optionalLine, optionalUserData);
          errorCode = -3;
          goto errorExit;
        }
      }
      redCreateProcedure(context, gpu, inlineProcedure->handleName, 0, inlineProcedure->outputDeclaration, inlineProcedure->procedureParameters, inlineProcedure->gpuCodeVertexMainProcedureName, gpuCodeAndProcedureHandles.gpuCodeVertex, inlineProcedure->gpuCodeFragmentMainProcedureName, gpuCodeAndProcedureHandles.gpuCodeFragment, inlineProcedure->state, inlineProcedure->stateExtension, 0, 0, &gpuCodeAndProcedureHandles.procedure, outStatuses, optionalFile, optionalLine, optionalUserData);
      if (gpuCodeAndProcedureHandles.procedure == 0) {
        redDestroyGpuCode(context, gpu, gpuCodeAndProcedureHandles.gpuCodeVertex, optionalFile, optionalLine, optionalUserData);
        if (gpuCodeAndProcedureHandles.gpuCodeFragment != 0) {
          redDestroyGpuCode(context, gpu, gpuCodeAndProcedureHandles.gpuCodeFragment, optionalFile, optionalLine, optionalUserData);
        }
        errorCode = -4;
        goto errorExit;
      }
      procedures->procedures[inlineProcedureUniqueKey] = gpuCodeAndProcedureHandles;
    }
    procedure = gpuCodeAndProcedureHandles.procedure;
  }

precompile:;

  {
    RedCallProceduresAndAddresses callPAs = {};
    redGetCallProceduresAndAddresses(context, gpu, &callPAs, 0, 0, 0, 0);
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
      } else if (errorCode == -5) {
        char desc[512] = "[redCallSetInlineProcedure] Queried by inlineProcedurePrecompileKey procedure handle is not valid.";
        memcpy(outStatuses->statusErrorDescription, desc, 512);
      }
    }
  }

exit:;

}

REDGPU_DECLSPEC void REDGPU_API redCallSetInlineProcedureCompute(RedHandleCalls calls, RedContext context, RedHandleGpu gpu, const char * inlineProcedurePrecompileKey, uint64_t inlineProcedureUniqueKey, const RedInlineProcedureCompute * inlineProcedure, RedStatuses * outStatuses, const char * optionalFile, int optionalLine, void * optionalUserData) {
  int errorCode = 0;

  RedHandleProcedure                             procedure  = 0;
  RedInlineProcedureGlobalMapComputeProcedures * procedures = 0;

  if (inlineProcedurePrecompileKey != 0) {
    std::string precompileKey = inlineProcedurePrecompileKey;
    RedInlineGpuCodeAndProcedureComputeHandles gpuCodeAndProcedureHandles = __REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapPrecompilesCompute[precompileKey];
    if (gpuCodeAndProcedureHandles.procedure == 0) {
      errorCode = -4;
      goto errorExit;
    }
    procedure = gpuCodeAndProcedureHandles.procedure;
    goto precompile;
  }

  {
    std::lock_guard<std::mutex> __mapComputeMutexScope(__REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapInlinesComputeMutex);
    procedures = __REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapInlinesCompute[calls];
    if (procedures == 0) {
      procedures = new(std::nothrow) RedInlineProcedureGlobalMapComputeProcedures();
      if (procedures == 0) {
        errorCode = -1;
      } else {
        __REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapInlinesCompute[calls] = procedures;
      }
    }
  }
  if (errorCode != 0) {
    goto errorExit;
  }

  {
    RedInlineGpuCodeAndProcedureComputeHandles gpuCodeAndProcedureHandles = procedures->procedures[inlineProcedureUniqueKey];
    if (gpuCodeAndProcedureHandles.procedure == 0) {
      gpuCodeAndProcedureHandles.context = context;
      gpuCodeAndProcedureHandles.gpu     = gpu;
      // NOTE(Constantine):
      // Not found, create and assign gpu code and procedure handles then.
      redCreateGpuCode(context, gpu, inlineProcedure->gpuCodeHandleName, inlineProcedure->gpuCodeIrBytesCount, inlineProcedure->gpuCodeIr, &gpuCodeAndProcedureHandles.gpuCode, outStatuses, optionalFile, optionalLine, optionalUserData);
      if (gpuCodeAndProcedureHandles.gpuCode == 0) {
        errorCode = -2;
        goto errorExit;
      }
      redCreateProcedureCompute(context, gpu, inlineProcedure->handleName, 0, inlineProcedure->procedureParameters, inlineProcedure->gpuCodeMainProcedureName, gpuCodeAndProcedureHandles.gpuCode, &gpuCodeAndProcedureHandles.procedure, outStatuses, optionalFile, optionalLine, optionalUserData);
      if (gpuCodeAndProcedureHandles.procedure == 0) {
        redDestroyGpuCode(context, gpu, gpuCodeAndProcedureHandles.gpuCode, optionalFile, optionalLine, optionalUserData);
        errorCode = -3;
        goto errorExit;
      }
      procedures->procedures[inlineProcedureUniqueKey] = gpuCodeAndProcedureHandles;
    }
    procedure = gpuCodeAndProcedureHandles.procedure;
  }

precompile:;

  {
    RedCallProceduresAndAddresses callPAs = {};
    redGetCallProceduresAndAddresses(context, gpu, &callPAs, 0, 0, 0, 0);
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
      } else if (errorCode == -4) {
        char desc[512] = "[redCallSetInlineProcedureCompute] Queried by inlineProcedurePrecompileKey procedure handle is not valid.";
        memcpy(outStatuses->statusErrorDescription, desc, 512);
      }
    }
  }

exit:;

}

REDGPU_DECLSPEC void REDGPU_API redBeforeDestroyCallsDestroyInlineProcedures(RedHandleCalls calls, const char * optionalFile, int optionalLine, void * optionalUserData) {
  {
    std::lock_guard<std::mutex> __mapMutexScope(__REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapInlinesMutex);
    RedInlineProcedureGlobalMapProcedures * procedures = __REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapInlines[calls];
    if (procedures != 0) {
      for (auto & pair : procedures->procedures) {
        redDestroyGpuCode(pair.second.context, pair.second.gpu, pair.second.gpuCodeVertex, optionalFile, optionalLine, optionalUserData);
        if (pair.second.gpuCodeFragment != 0) {
          redDestroyGpuCode(pair.second.context, pair.second.gpu, pair.second.gpuCodeFragment, optionalFile, optionalLine, optionalUserData);
        }
        redDestroyProcedure(pair.second.context, pair.second.gpu, pair.second.procedure, optionalFile, optionalLine, optionalUserData);
      }
      delete procedures;
      __REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapInlines.erase(calls);
    }
  }
  {
    std::lock_guard<std::mutex> __mapComputeMutexScope(__REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapInlinesComputeMutex);
    RedInlineProcedureGlobalMapComputeProcedures * procedures = __REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapInlinesCompute[calls];
    if (procedures != 0) {
      for (auto & pair : procedures->procedures) {
        redDestroyGpuCode(pair.second.context, pair.second.gpu, pair.second.gpuCode, optionalFile, optionalLine, optionalUserData);
        redDestroyProcedure(pair.second.context, pair.second.gpu, pair.second.procedure, optionalFile, optionalLine, optionalUserData);
      }
      delete procedures;
      __REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapInlinesCompute.erase(calls);
    }
  }
}

REDGPU_DECLSPEC void REDGPU_API redDestroyAllInlineProcedurePrecompiles(const char * optionalFile, int optionalLine, void * optionalUserData) {
  for (auto & pair : __REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapPrecompiles) {
    redDestroyGpuCode(pair.second.context, pair.second.gpu, pair.second.gpuCodeVertex, optionalFile, optionalLine, optionalUserData);
    if (pair.second.gpuCodeFragment != 0) {
      redDestroyGpuCode(pair.second.context, pair.second.gpu, pair.second.gpuCodeFragment, optionalFile, optionalLine, optionalUserData);
    }
    redDestroyProcedure(pair.second.context, pair.second.gpu, pair.second.procedure, optionalFile, optionalLine, optionalUserData);
  }
  for (auto & pair : __REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapPrecompilesCompute) {
    redDestroyGpuCode(pair.second.context, pair.second.gpu, pair.second.gpuCode, optionalFile, optionalLine, optionalUserData);
    redDestroyProcedure(pair.second.context, pair.second.gpu, pair.second.procedure, optionalFile, optionalLine, optionalUserData);
  }
  __REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapPrecompiles        = {};
  __REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapPrecompilesCompute = {};
}

REDGPU_DECLSPEC void REDGPU_API redDestroyAllInlineProcedureMapOutputDeclaration(const char * optionalFile, int optionalLine, void * optionalUserData) {
  for (auto & pair : __REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapOutputDeclarations) {
    redDestroyOutputDeclaration(pair.second.context, pair.second.gpu, (RedHandleOutputDeclaration)pair.second.handle, optionalFile, optionalLine, optionalUserData);
  }
  __REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapOutputDeclarations = {};
}

REDGPU_DECLSPEC void REDGPU_API redDestroyAllInlineProcedureMapGreenStructDeclaration(const char * optionalFile, int optionalLine, void * optionalUserData) {
  for (auto & pair : __REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapGreenStructDeclarations) {
    RedInlineGreenStructDeclaration * v = pair.second;    
    if (v == 0) {
      continue;    
    }
    redDestroyStructDeclaration(v->context, v->gpu, v->structDeclaration, optionalFile, optionalLine, optionalUserData);
    delete[] v;
  }
  __REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapGreenStructDeclarations = {};
}

REDGPU_DECLSPEC void REDGPU_API redDestroyAllInlineProcedureMapProcedureParameters(const char * optionalFile, int optionalLine, void * optionalUserData) {
  for (auto & pair : __REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapProcedureParameters) {
    redDestroyProcedureParameters(pair.second.context, pair.second.gpu, (RedHandleProcedureParameters)pair.second.handle, optionalFile, optionalLine, optionalUserData);
  }
  __REDGPU_INLINE_PROCEDURE_GLOBAL_1fab7553629232e5a6048b43192363843eb878d8_mapProcedureParameters = {};
}

