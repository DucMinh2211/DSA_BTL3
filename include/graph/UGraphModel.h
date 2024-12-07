/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   UGraphModel.h
 * Author: LTSACH
 *
 * Created on 24 August 2020, 15:16
 */

#ifndef UGRAPHMODEL_H
#define UGRAPHMODEL_H

#include "graph/AbstractGraph.h"
#include "stacknqueue/PriorityQueue.h"

//////////////////////////////////////////////////////////////////////
///////////// UGraphModel: Undirected Graph Model ////////////////////
//////////////////////////////////////////////////////////////////////

template <class T>
class UGraphModel : public AbstractGraph<T>
{
private:
public:
    // class UGraphAlgorithm;
    // friend class UGraphAlgorithm;

    UGraphModel(
        bool (*vertexEQ)(T &, T &),
        string (*vertex2str)(T &)) : AbstractGraph<T>(vertexEQ, vertex2str)
    {
    }

    void connect(T from, T to, float weight = 0)
    {
        // TODO
        typename VertexNode* from_node = this->getVertexNode(from);
        typename VertexNode* to_node = this->getVertexNode(to);
        if (!from_node or !to_node) throw VertexNotFoundException();
        from_node->connect(to_node, weight);
        to_node->connect(from_node, weight);
    }
    void disconnect(T from, T to)
    {
        // TODO
		typename VertexNode* from_node = this->getVertexNode(from);
        typename VertexNode* to_node = this->getVertexNode(to);
        if (!from_node or !to_node) throw VertexNotFoundException();
        if (from_node->equals(to_node)) {
        	Edge* connect_edge = from_node->getEdge(to_node);
        	if (!connect_edge) throw EdgeNotFoundException();
        	from_node->removeTo(to_node);
        	return;
        }
        Edge* from_edge = from_node->getEdge(to_node);
        Edge* to_edge = to_node->getEdge(from_node);
        if (!from_edge or !to_edge) throw EdgeNotFoundException();
        from_node->removeTo(to_node);
        to_node->removeTo(from_node);
    }
    void remove(T vertex)
    {
        // TODO
    }
    static UGraphModel<T> *create(
        T *vertices, int nvertices, Edge<T> *edges, int nedges,
        bool (*vertexEQ)(T &, T &),
        string (*vertex2str)(T &))
    {
        // TODO
    }
};

#endif /* UGRAPHMODEL_H */
