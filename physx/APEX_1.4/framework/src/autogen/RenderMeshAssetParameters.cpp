//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//  * Neither the name of NVIDIA CORPORATION nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
// OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Copyright (c) 2018 NVIDIA Corporation. All rights reserved.

// This file was generated by NvParameterized/scripts/GenParameterized.pl


#include "RenderMeshAssetParameters.h"
#include <string.h>
#include <stdlib.h>

using namespace NvParameterized;

namespace nvidia
{
namespace apex
{

using namespace RenderMeshAssetParametersNS;

const char* const RenderMeshAssetParametersFactory::vptr =
    NvParameterized::getVptr<RenderMeshAssetParameters, RenderMeshAssetParameters::ClassAlignment>();

const uint32_t NumParamDefs = 11;
static NvParameterized::DefinitionImpl* ParamDefTable; // now allocated in buildTree [NumParamDefs];


static const size_t ParamLookupChildrenTable[] =
{
	1, 3, 5, 7, 8, 9, 10, 2, 4, 6,
};

#define TENUM(type) nvidia::##type
#define CHILDREN(index) &ParamLookupChildrenTable[index]
static const NvParameterized::ParamLookupNode ParamLookupTable[NumParamDefs] =
{
	{ TYPE_STRUCT, false, 0, CHILDREN(0), 7 },
	{ TYPE_ARRAY, true, (size_t)(&((ParametersStruct*)0)->submeshes), CHILDREN(7), 1 }, // submeshes
	{ TYPE_REF, false, 1 * sizeof(NvParameterized::Interface*), NULL, 0 }, // submeshes[]
	{ TYPE_ARRAY, true, (size_t)(&((ParametersStruct*)0)->materialNames), CHILDREN(8), 1 }, // materialNames
	{ TYPE_STRING, false, 1 * sizeof(NvParameterized::DummyStringStruct), NULL, 0 }, // materialNames[]
	{ TYPE_ARRAY, true, (size_t)(&((ParametersStruct*)0)->partBounds), CHILDREN(9), 1 }, // partBounds
	{ TYPE_BOUNDS3, false, 1 * sizeof(physx::PxBounds3), NULL, 0 }, // partBounds[]
	{ TYPE_U32, false, (size_t)(&((ParametersStruct*)0)->textureUVOrigin), NULL, 0 }, // textureUVOrigin
	{ TYPE_U32, false, (size_t)(&((ParametersStruct*)0)->boneCount), NULL, 0 }, // boneCount
	{ TYPE_BOOL, false, (size_t)(&((ParametersStruct*)0)->deleteStaticBuffersAfterUse), NULL, 0 }, // deleteStaticBuffersAfterUse
	{ TYPE_BOOL, false, (size_t)(&((ParametersStruct*)0)->isReferenced), NULL, 0 }, // isReferenced
};


bool RenderMeshAssetParameters::mBuiltFlag = false;
NvParameterized::MutexType RenderMeshAssetParameters::mBuiltFlagMutex;

RenderMeshAssetParameters::RenderMeshAssetParameters(NvParameterized::Traits* traits, void* buf, int32_t* refCount) :
	NvParameters(traits, buf, refCount)
{
	//mParameterizedTraits->registerFactory(className(), &RenderMeshAssetParametersFactoryInst);

	if (!buf) //Do not init data if it is inplace-deserialized
	{
		initDynamicArrays();
		initStrings();
		initReferences();
		initDefaults();
	}
}

RenderMeshAssetParameters::~RenderMeshAssetParameters()
{
	freeStrings();
	freeReferences();
	freeDynamicArrays();
}

void RenderMeshAssetParameters::destroy()
{
	// We cache these fields here to avoid overwrite in destructor
	bool doDeallocateSelf = mDoDeallocateSelf;
	NvParameterized::Traits* traits = mParameterizedTraits;
	int32_t* refCount = mRefCount;
	void* buf = mBuffer;

	this->~RenderMeshAssetParameters();

	NvParameters::destroy(this, traits, doDeallocateSelf, refCount, buf);
}

const NvParameterized::DefinitionImpl* RenderMeshAssetParameters::getParameterDefinitionTree(void)
{
	if (!mBuiltFlag) // Double-checked lock
	{
		NvParameterized::MutexType::ScopedLock lock(mBuiltFlagMutex);
		if (!mBuiltFlag)
		{
			buildTree();
		}
	}

	return(&ParamDefTable[0]);
}

const NvParameterized::DefinitionImpl* RenderMeshAssetParameters::getParameterDefinitionTree(void) const
{
	RenderMeshAssetParameters* tmpParam = const_cast<RenderMeshAssetParameters*>(this);

	if (!mBuiltFlag) // Double-checked lock
	{
		NvParameterized::MutexType::ScopedLock lock(mBuiltFlagMutex);
		if (!mBuiltFlag)
		{
			tmpParam->buildTree();
		}
	}

	return(&ParamDefTable[0]);
}

NvParameterized::ErrorType RenderMeshAssetParameters::getParameterHandle(const char* long_name, Handle& handle) const
{
	ErrorType Ret = NvParameters::getParameterHandle(long_name, handle);
	if (Ret != ERROR_NONE)
	{
		return(Ret);
	}

	size_t offset;
	void* ptr;

	getVarPtr(handle, ptr, offset);

	if (ptr == NULL)
	{
		return(ERROR_INDEX_OUT_OF_RANGE);
	}

	return(ERROR_NONE);
}

NvParameterized::ErrorType RenderMeshAssetParameters::getParameterHandle(const char* long_name, Handle& handle)
{
	ErrorType Ret = NvParameters::getParameterHandle(long_name, handle);
	if (Ret != ERROR_NONE)
	{
		return(Ret);
	}

	size_t offset;
	void* ptr;

	getVarPtr(handle, ptr, offset);

	if (ptr == NULL)
	{
		return(ERROR_INDEX_OUT_OF_RANGE);
	}

	return(ERROR_NONE);
}

void RenderMeshAssetParameters::getVarPtr(const Handle& handle, void*& ptr, size_t& offset) const
{
	ptr = getVarPtrHelper(&ParamLookupTable[0], const_cast<RenderMeshAssetParameters::ParametersStruct*>(&parameters()), handle, offset);
}


/* Dynamic Handle Indices */
/* [0] - submeshes (not an array of structs) */
/* [0] - materialNames (not an array of structs) */

void RenderMeshAssetParameters::freeParameterDefinitionTable(NvParameterized::Traits* traits)
{
	if (!traits)
	{
		return;
	}

	if (!mBuiltFlag) // Double-checked lock
	{
		return;
	}

	NvParameterized::MutexType::ScopedLock lock(mBuiltFlagMutex);

	if (!mBuiltFlag)
	{
		return;
	}

	for (uint32_t i = 0; i < NumParamDefs; ++i)
	{
		ParamDefTable[i].~DefinitionImpl();
	}

	traits->free(ParamDefTable);

	mBuiltFlag = false;
}

#define PDEF_PTR(index) (&ParamDefTable[index])

void RenderMeshAssetParameters::buildTree(void)
{

	uint32_t allocSize = sizeof(NvParameterized::DefinitionImpl) * NumParamDefs;
	ParamDefTable = (NvParameterized::DefinitionImpl*)(mParameterizedTraits->alloc(allocSize));
	memset(ParamDefTable, 0, allocSize);

	for (uint32_t i = 0; i < NumParamDefs; ++i)
	{
		NV_PARAM_PLACEMENT_NEW(ParamDefTable + i, NvParameterized::DefinitionImpl)(*mParameterizedTraits);
	}

	// Initialize DefinitionImpl node: nodeIndex=0, longName=""
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[0];
		ParamDef->init("", TYPE_STRUCT, "STRUCT", true);






	}

	// Initialize DefinitionImpl node: nodeIndex=1, longName="submeshes"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[1];
		ParamDef->init("submeshes", TYPE_ARRAY, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("INCLUDED", uint64_t(1), true);
		ParamDefTable[1].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#else

		static HintImpl HintTable[3];
		static Hint* HintPtrTable[3] = { &HintTable[0], &HintTable[1], &HintTable[2], };
		HintTable[0].init("INCLUDED", uint64_t(1), true);
		HintTable[1].init("longDescription", "This is the array of submeshes which comprise the mesh.  Triangles are grouped\ninto submeshes, which correspond to a unique material name.  The distinction\nneed not be just material; this grouping may distinguish any render state which\nrequires a separate draw call.\n", true);
		HintTable[2].init("shortDescription", "Array of submeshes", true);
		ParamDefTable[1].setHints((const NvParameterized::Hint**)HintPtrTable, 3);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */


		static const char* const RefVariantVals[] = { "SubmeshParameters" };
		ParamDefTable[1].setRefVariantVals((const char**)RefVariantVals, 1);


		ParamDef->setArraySize(-1);
		static const uint8_t dynHandleIndices[1] = { 0, };
		ParamDef->setDynamicHandleIndicesMap(dynHandleIndices, 1);

	}

	// Initialize DefinitionImpl node: nodeIndex=2, longName="submeshes[]"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[2];
		ParamDef->init("submeshes", TYPE_REF, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("INCLUDED", uint64_t(1), true);
		ParamDefTable[2].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#else

		static HintImpl HintTable[3];
		static Hint* HintPtrTable[3] = { &HintTable[0], &HintTable[1], &HintTable[2], };
		HintTable[0].init("INCLUDED", uint64_t(1), true);
		HintTable[1].init("longDescription", "This is the array of submeshes which comprise the mesh.  Triangles are grouped\ninto submeshes, which correspond to a unique material name.  The distinction\nneed not be just material; this grouping may distinguish any render state which\nrequires a separate draw call.\n", true);
		HintTable[2].init("shortDescription", "Array of submeshes", true);
		ParamDefTable[2].setHints((const NvParameterized::Hint**)HintPtrTable, 3);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */


		static const char* const RefVariantVals[] = { "SubmeshParameters" };
		ParamDefTable[2].setRefVariantVals((const char**)RefVariantVals, 1);



	}

	// Initialize DefinitionImpl node: nodeIndex=3, longName="materialNames"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[3];
		ParamDef->init("materialNames", TYPE_ARRAY, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("longDescription", "The material names which distinguish the submeshes (see submeshes).", true);
		HintTable[1].init("shortDescription", "Array of material names", true);
		ParamDefTable[3].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */




		ParamDef->setArraySize(-1);
		static const uint8_t dynHandleIndices[1] = { 0, };
		ParamDef->setDynamicHandleIndicesMap(dynHandleIndices, 1);

	}

	// Initialize DefinitionImpl node: nodeIndex=4, longName="materialNames[]"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[4];
		ParamDef->init("materialNames", TYPE_STRING, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("longDescription", "The material names which distinguish the submeshes (see submeshes).", true);
		HintTable[1].init("shortDescription", "Array of material names", true);
		ParamDefTable[4].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=5, longName="partBounds"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[5];
		ParamDef->init("partBounds", TYPE_ARRAY, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("longDescription", "Array of axis-aligned bounding boxes for each part.  The bounds for part i are in partBounds[i].", true);
		HintTable[1].init("shortDescription", "The AABBs of each mesh part", true);
		ParamDefTable[5].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */




		ParamDef->setArraySize(-1);
	}

	// Initialize DefinitionImpl node: nodeIndex=6, longName="partBounds[]"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[6];
		ParamDef->init("partBounds", TYPE_BOUNDS3, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("longDescription", "Array of axis-aligned bounding boxes for each part.  The bounds for part i are in partBounds[i].", true);
		HintTable[1].init("shortDescription", "The AABBs of each mesh part", true);
		ParamDefTable[6].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=7, longName="textureUVOrigin"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[7];
		ParamDef->init("textureUVOrigin", TYPE_U32, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("longDescription", "The texture origin convention to use for this mesh.  See TextureUVOrigin.", true);
		HintTable[1].init("shortDescription", "Texture origin convention", true);
		ParamDefTable[7].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=8, longName="boneCount"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[8];
		ParamDef->init("boneCount", TYPE_U32, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("longDescription", "The number of mesh-skinning bones.  For destructible assets, this is the same as the number of parts.", true);
		HintTable[1].init("shortDescription", "The number of mesh-skinning bones", true);
		ParamDefTable[8].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=9, longName="deleteStaticBuffersAfterUse"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[9];
		ParamDef->init("deleteStaticBuffersAfterUse", TYPE_BOOL, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("longDescription", "If set, static data buffers will be deleted after they are used in createRenderResources.", true);
		HintTable[1].init("shortDescription", "If set, static data buffers will be deleted after they are used in createRenderResources.", true);
		ParamDefTable[9].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=10, longName="isReferenced"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[10];
		ParamDef->init("isReferenced", TYPE_BOOL, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("shortDescription", "Is the render mesh asset referenced in other assets", true);
		ParamDefTable[10].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// SetChildren for: nodeIndex=0, longName=""
	{
		static Definition* Children[7];
		Children[0] = PDEF_PTR(1);
		Children[1] = PDEF_PTR(3);
		Children[2] = PDEF_PTR(5);
		Children[3] = PDEF_PTR(7);
		Children[4] = PDEF_PTR(8);
		Children[5] = PDEF_PTR(9);
		Children[6] = PDEF_PTR(10);

		ParamDefTable[0].setChildren(Children, 7);
	}

	// SetChildren for: nodeIndex=1, longName="submeshes"
	{
		static Definition* Children[1];
		Children[0] = PDEF_PTR(2);

		ParamDefTable[1].setChildren(Children, 1);
	}

	// SetChildren for: nodeIndex=3, longName="materialNames"
	{
		static Definition* Children[1];
		Children[0] = PDEF_PTR(4);

		ParamDefTable[3].setChildren(Children, 1);
	}

	// SetChildren for: nodeIndex=5, longName="partBounds"
	{
		static Definition* Children[1];
		Children[0] = PDEF_PTR(6);

		ParamDefTable[5].setChildren(Children, 1);
	}

	mBuiltFlag = true;

}
void RenderMeshAssetParameters::initStrings(void)
{
}

void RenderMeshAssetParameters::initDynamicArrays(void)
{
	submeshes.buf = NULL;
	submeshes.isAllocated = true;
	submeshes.elementSize = sizeof(NvParameterized::Interface*);
	submeshes.arraySizes[0] = 0;
	materialNames.buf = NULL;
	materialNames.isAllocated = true;
	materialNames.elementSize = sizeof(NvParameterized::DummyStringStruct);
	materialNames.arraySizes[0] = 0;
	partBounds.buf = NULL;
	partBounds.isAllocated = true;
	partBounds.elementSize = sizeof(physx::PxBounds3);
	partBounds.arraySizes[0] = 0;
}

void RenderMeshAssetParameters::initDefaults(void)
{

	freeStrings();
	freeReferences();
	freeDynamicArrays();
	textureUVOrigin = uint32_t(0);
	boneCount = uint32_t(0);
	deleteStaticBuffersAfterUse = bool(false);
	isReferenced = bool(false);

	initDynamicArrays();
	initStrings();
	initReferences();
}

void RenderMeshAssetParameters::initReferences(void)
{
}

void RenderMeshAssetParameters::freeDynamicArrays(void)
{
	if (submeshes.isAllocated && submeshes.buf)
	{
		mParameterizedTraits->free(submeshes.buf);
	}
	if (materialNames.isAllocated && materialNames.buf)
	{
		mParameterizedTraits->free(materialNames.buf);
	}
	if (partBounds.isAllocated && partBounds.buf)
	{
		mParameterizedTraits->free(partBounds.buf);
	}
}

void RenderMeshAssetParameters::freeStrings(void)
{

	for (int i = 0; i < materialNames.arraySizes[0]; ++i)
	{
		if (materialNames.buf[i].isAllocated && materialNames.buf[i].buf)
		{
			mParameterizedTraits->strfree((char*)materialNames.buf[i].buf);
		}
	}
}

void RenderMeshAssetParameters::freeReferences(void)
{

	for (int i = 0; i < submeshes.arraySizes[0]; ++i)
	{
		if (submeshes.buf[i])
		{
			submeshes.buf[i]->destroy();
		}
	}
}

} // namespace apex
} // namespace nvidia
