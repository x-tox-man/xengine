// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2016
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 2.1.0 (2016/01/25)

#include <GTEnginePCH.h>
#include <LowLevel/GteLogger.h>
#include <Mathematics/GteVETManifoldMesh.h>
using namespace gte;

VETManifoldMesh::~VETManifoldMesh()
{
    for (auto& element : mVMap)
    {
        delete element.second;
    }
}

VETManifoldMesh::VETManifoldMesh(VCreator vCreator, ECreator eCreator, TCreator tCreator)
    :
    ETManifoldMesh(eCreator, tCreator),
    mVCreator(vCreator ? vCreator : CreateVertex)
{
}

VETManifoldMesh::VETManifoldMesh(VETManifoldMesh const& mesh)
{
    *this = mesh;
}

VETManifoldMesh& VETManifoldMesh::operator=(VETManifoldMesh const& mesh)
{
    Clear();
    mVCreator = mesh.mVCreator;
    ETManifoldMesh::operator=(mesh);
    return *this;
}

VETManifoldMesh::VMap const& VETManifoldMesh::GetVertices() const
{
    return mVMap;
}

VETManifoldMesh::Triangle* VETManifoldMesh::Insert(int v0, int v1, int v2)
{
    Triangle* tri = ETManifoldMesh::Insert(v0, v1, v2);
    if (!tri)
    {
        return nullptr;
    }

    for (int i = 0; i < 3; ++i)
    {
        int vIndex = tri->V[i];
        auto vItem = mVMap.find(vIndex);
        Vertex* vertex;
        if (vItem == mVMap.end())
        {
            vertex = mVCreator(vIndex);
            mVMap[vIndex] = vertex;
        }
        else
        {
            vertex = vItem->second;
        }

        vertex->TAdjacent.insert(tri);

        for (int j = 0; j < 3; ++j)
        {
            Edge* edge = tri->E[j];
            if (edge)
            {
                if (edge->V[0] == vIndex)
                {
                    vertex->VAdjacent.insert(edge->V[1]);
                    vertex->EAdjacent.insert(edge);
                }
                else if (edge->V[1] == vIndex)
                {
                    vertex->VAdjacent.insert(edge->V[0]);
                    vertex->EAdjacent.insert(edge);
                }
            }
            else
            {
                LogError("Malformed mesh: Triangle edges must not be null.");
                return nullptr;
            }
        }
    }

    return tri;
}

bool VETManifoldMesh::Remove(int v0, int v1, int v2)
{
    auto tItem = mTMap.find(TriangleKey<true>(v0, v1, v2));
    if (tItem == mTMap.end())
    {
        return false;
    }

    Triangle* tri = tItem->second;
    for (int i = 0; i < 3; ++i)
    {
        int vIndex = tri->V[i];
        auto vItem = mVMap.find(vIndex);
        if (vItem != mVMap.end())
        {
            Vertex* vertex = vItem->second;
            for (int j = 0; j < 3; ++j)
            {
                Edge* edge = tri->E[j];
                if (edge)
                {
                    if (edge->T[0] && !edge->T[1])
                    {
                        if (edge->V[0] == vIndex)
                        {
                            vertex->VAdjacent.erase(edge->V[1]);
                            vertex->EAdjacent.erase(edge);
                        }
                        else if (edge->V[1] == vIndex)
                        {
                            vertex->VAdjacent.erase(edge->V[0]);
                            vertex->EAdjacent.erase(edge);
                        }
                    }
                }
                else
                {
                    LogError("Malformed mesh: Triangle edges must not be null.");
                    return false;
                }
            }

            vertex->TAdjacent.erase(tri);

            if (vertex->TAdjacent.size() == 0)
            {
                LogAssert(vertex->VAdjacent.size() == 0 && vertex->EAdjacent.size() == 0,
                    "Malformed mesh: Inconsistent vertex adjacency information.");

                mVMap.erase(vItem);
                delete vertex;
            }
        }
        else
        {
            LogError("Malformed mesh: Vertex must exist in the mesh.");
            return false;
        }
    }

    return ETManifoldMesh::Remove(v0, v1, v2);
}

void VETManifoldMesh::Clear()
{
    for (auto& element : mVMap)
    {
        delete element.second;
    }

    mVMap.clear();

    ETManifoldMesh::Clear();
}

void VETManifoldMesh::Print(std::ostream& output) const
{
    if (output.bad())
    {
        LogError("Output stream is invalid.");
        return;
    }

    std::map<Edge*, int> eIndex;
    std::map<Triangle*, int> tIndex;
    ETManifoldMesh::AssignUniqueIndices(eIndex, tIndex);
    PrintVertices(output, eIndex, tIndex);
    PrintEdgesTriangles(output, eIndex, tIndex);
}

void VETManifoldMesh::PrintVertices(std::ostream& output, std::map<Edge*, int>& eIndex,
    std::map<Triangle*, int>& tIndex) const
{
    output << "vertex quantity = " << mVMap.size() << std::endl;
    for (auto const& element : mVMap)
    {
        Vertex const& vertex = *element.second;
        output << 'v' << vertex.V << " < ";
        for (auto const& vAdj : vertex.VAdjacent)
        {
            output << 'v' << vAdj << ' ';
        }
        output << "> < ";
        for (auto const& eAdj : vertex.EAdjacent)
        {
            output << 'e' << eIndex[eAdj] << ' ';
        }
        output << "> < ";
        for (auto const& tAdj : vertex.TAdjacent)
        {
            output << 't' << tIndex[tAdj] << ' ';
        }
        output << ">" << std::endl;
    }
    output << std::endl;
}

VETManifoldMesh::Vertex* VETManifoldMesh::CreateVertex(int vIndex)
{
    return new Vertex(vIndex);
}

VETManifoldMesh::Vertex::~Vertex()
{
}

VETManifoldMesh::Vertex::Vertex(int vIndex)
    :
    V(vIndex)
{
}
