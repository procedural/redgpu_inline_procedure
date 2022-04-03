#pragma once

#ifdef _WIN32
#include "C:/RedGpuSDK/redgpu.h"
#include "C:/github/procedural/redgpu_green_struct/redgpu_green_struct.h"
#endif
#ifdef __linux__
#include "/opt/RedGpuSDK/redgpu.h"
#include "/opt/github/procedural/redgpu_green_struct/redgpu_green_struct.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct RedInlineProcedure {
  const char *                 handleName;
  RedHandleOutputDeclaration   outputDeclaration;
  RedHandleProcedureParameters procedureParameters;
  const char *                 gpuCodeVertexMainProcedureName;
  const char *                 gpuCodeVertexHandleName;
  uint64_t                     gpuCodeVertexIrBytesCount;
  const void *                 gpuCodeVertexIr;
  const char *                 gpuCodeFragmentMainProcedureName;
  const char *                 gpuCodeFragmentHandleName;
  uint64_t                     gpuCodeFragmentIrBytesCount;
  const void *                 gpuCodeFragmentIr;
  const RedProcedureState *    state;
  const void *                 stateExtension;
} RedInlineProcedure;

typedef struct RedInlineProcedureCompute {
  const char *                 handleName;
  RedHandleProcedureParameters procedureParameters;
  const char *                 gpuCodeMainProcedureName;
  const char *                 gpuCodeHandleName;
  uint64_t                     gpuCodeIrBytesCount;
  const void *                 gpuCodeIr;
} RedInlineProcedureCompute;

REDGPU_DECLSPEC RedHandleOutputDeclaration   REDGPU_API redInlineProcedureMapGetOutputDeclaration      (const char * key);
REDGPU_DECLSPEC void                         REDGPU_API redInlineProcedureMapGetGreenStructDeclaration (const char * key, GreenStructDeclaration * outGreenStructDeclaration);
REDGPU_DECLSPEC RedHandleProcedureParameters REDGPU_API redInlineProcedureMapGetProcedureParameters    (const char * key);

REDGPU_DECLSPEC void REDGPU_API redInlineProcedureMapSetOutputDeclaration      (const char * key, RedContext context, RedHandleGpu gpu, RedHandleOutputDeclaration outputDeclaration);
REDGPU_DECLSPEC void REDGPU_API redInlineProcedureMapSetGreenStructDeclaration (const char * key, RedContext context, RedHandleGpu gpu, const GreenStructDeclaration * greenStructDeclaration);
REDGPU_DECLSPEC void REDGPU_API redInlineProcedureMapSetProcedureParameters    (const char * key, RedContext context, RedHandleGpu gpu, RedHandleProcedureParameters procedureParameters);

REDGPU_DECLSPEC void REDGPU_API redCreateInlineProcedurePrecompile             (RedContext context, RedHandleGpu gpu, const char * inlineProcedurePrecompileUniqueKey, const RedInlineProcedure * inlineProcedure, RedStatuses * outStatuses, const char * optionalFile, int optionalLine, void * optionalUserData);
REDGPU_DECLSPEC void REDGPU_API redCreateInlineProcedurePrecompileCompute      (RedContext context, RedHandleGpu gpu, const char * inlineProcedurePrecompileUniqueKey, const RedInlineProcedureCompute * inlineProcedure, RedStatuses * outStatuses, const char * optionalFile, int optionalLine, void * optionalUserData);

REDGPU_DECLSPEC void REDGPU_API redCallSetInlineProcedure                      (RedHandleCalls calls, RedContext context, RedHandleGpu gpu, const char * inlineProcedurePrecompileKey, uint64_t inlineProcedureUniqueKey, const RedInlineProcedure * inlineProcedure, RedStatuses * outStatuses, const char * optionalFile, int optionalLine, void * optionalUserData);
REDGPU_DECLSPEC void REDGPU_API redCallSetInlineProcedureCompute               (RedHandleCalls calls, RedContext context, RedHandleGpu gpu, const char * inlineProcedurePrecompileKey, uint64_t inlineProcedureUniqueKey, const RedInlineProcedureCompute * inlineProcedure, RedStatuses * outStatuses, const char * optionalFile, int optionalLine, void * optionalUserData);

REDGPU_DECLSPEC void REDGPU_API redBeforeDestroyCallsDestroyInlineProcedures          (RedHandleCalls calls, const char * optionalFile, int optionalLine, void * optionalUserData);
REDGPU_DECLSPEC void REDGPU_API redDestroyAllInlineProcedurePrecompiles               (const char * optionalFile, int optionalLine, void * optionalUserData);
REDGPU_DECLSPEC void REDGPU_API redDestroyAllInlineProcedureMapOutputDeclaration      (const char * optionalFile, int optionalLine, void * optionalUserData);
REDGPU_DECLSPEC void REDGPU_API redDestroyAllInlineProcedureMapGreenStructDeclaration (const char * optionalFile, int optionalLine, void * optionalUserData);
REDGPU_DECLSPEC void REDGPU_API redDestroyAllInlineProcedureMapProcedureParameters    (const char * optionalFile, int optionalLine, void * optionalUserData);

#ifdef __cplusplus
}
#endif
