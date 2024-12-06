/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DGraphModel.h
 * Author: LTSACH
 *
 * Created on 23 August 2020, 19:36
 */

#ifndef DGRAPHMODEL_H
#define DGRAPHMODEL_H
#include "graph/AbstractGraph.h"
#include <queue>
#include <stack>
#include "hash/xmap.h"
// #include "stacknqueue/PriorityQueue.h"
// #include "sorting/DLinkedListSE.h"


//////////////////////////////////////////////////////////////////////
///////////// GraphModel: Directed Graph Model    ////////////////////
//////////////////////////////////////////////////////////////////////


template<class T>
class DGraphModel: public AbstractGraph<T>{
private:
public:
    DGraphModel(
            bool (*vertexEQ)(T&, T&), 
            string (*vertex2str)(T&) ): 
        AbstractGraph<T>(vertexEQ, vertex2str){
    }
    
    void connect(T from, T to, float weight=0){
        //TODO
        typename VertexNode* from_node = this->getVertexNode(from);
        typename VertexNode* to_node = this->getVertexNode(to);
        if (!from_node or !to_node) throw VertexNotFoundException();
        from_node->connect(to_node, weight);
    }
    void disconnect(T from, T to){
        //TODO
        typename VertexNode* from_node = this->getVertexNode(from);
        typename VertexNode* to_node = this->getVertexNode(to);
        if (!from_node or !to_node) throw VertexNotFoundException();
        Edge* connect_edge = from_node->getEdge(to_node);
        if (!connect_edge) throw EdgeNotFoundException();
        from_node->removeTo(to_node);
    }
    void remove(T vertex){
        //TODO
        typename VertexNode* rmv_node = this->getVertexNode(vertex);
        if (!rmv_node) throw VertexNotFoundException();
        for (typename VertexNode node : this->nodeList) {
            node->removeTo(rmv_node);
            rmv_node->removeTo(node);
        }
        this->nodeList.removeItem(rmv_node);
    }
    
    static DGraphModel<T>* create(
            T* vertices, int nvertices, Edge<T>* edges, int nedges,
            bool (*vertexEQ)(T&, T&),
            string (*vertex2str)(T&)){
        //TODO
        DGraphModel<T>* graph = new DGraphModel<T>(vertexEQ, vertex2str);

        for (int i = 0; i < nvertices; ++i) {
            graph->add(vertices[i]);
        }

        for (int i = 0; i < nedges; ++i) {
            graph->connect(edges[i].from, edges[i].to, edges[i].weight);
        }

        return graph;
    }
};

#endif /* DGRAPHMODEL_H */

