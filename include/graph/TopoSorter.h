/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TopoSorter.h
 * Author: ltsach
 *
 * Created on July 11, 2021, 10:21 PM
 */

#ifndef TOPOSORTER_H
#define TOPOSORTER_H
#include "graph/DGraphModel.h"
#include "list/DLinkedList.h"
#include "sorting/DLinkedListSE.h"
#include "stacknqueue/Queue.h"
#include "hash/xMap.h"

template<class T>
class TopoSorter{
public:
    static int DFS;
    static int BFS; 
    
protected:
    DGraphModel<T>* graph;
    int (*hash_code)(T&, int);
    
public:
    TopoSorter(DGraphModel<T>* graph, int (*hash_code)(T&, int)=0){
        //TODO
        this->graph = graph;
        this->hash_code = hash_code;
    }   
    DLinkedList<T> sort(int mode=0, bool sorted=true){
        //TODO
        if (mode) {
            return bfsSort(sorted);
        }
        return dfsSort(sorted);
    }
    DLinkedList<T> bfsSort(bool sorted=true){ 
        //TODO
        DLinkedListSE<T> vertices_list;
        DLinkedListSE<T> vertices_tp_sorted;
        for (T vertex : graph){
            vertices_list.add(vertex);
        }
        if (sorted) {
            vertices_list.sort();
        }

        // Tạo xMap vertex2in_degree
        xMap<T, int> in_degree = vertex2inDegree(hash_code);
        for (T vertex : vertices_list) {
            in_degree.put(vertex, graph->inDegree(vertex));
        }
        // 
        Queue<T> q(nullptr, graph->vertexEQ);
        // Thêm các đỉnh in_degree = 0 vào q
        for (T vertex : vertices_list) {
            if (in_degree.get(vertex) == 0) q.push(vertex);
        }
        // BFS
        while (not q.empty()) {
            T front_vertex = q.pop();
            vertices_tp_sorted.add(front_vertex);
            // Giảm in_degree của các outward vertices
            DLinkedList<T> front_outward_vertices = graph->getOutwardEdges(front_vertex);
            for (T outward_vertex : front_outward_vertices) {
                in_degree.put(outward_vertex, in_degree.get(outward_vertex) - 1);
                if (in_degree.get(outward_vertex) == 0) q.push(outward_vertex);
            }
        }
        return vertices_tp_sorted;
    }

    DLinkedList<T> dfsSort(bool sorted=true){
        //TODO
        DLinkedListSE<T> vertices_list;
        DLinkedListSE<T> vertices_tp_sorted;
        for (T vertex : graph){
            vertices_list.add(vertex);
        }
        if (sorted) {
            vertices_list.sort();
        }
        // Tạo visited map với giá trị mặc định là false
        xMap<T, bool> visited(hash_code, vertices_list.size());
        for (T vertex : vertices_list) {
            visited.put(vertex, false);
        }

        // Hàm đệ quy DFS
        auto dfsVisit = [&](T vertex, auto& dfsVisit) -> void {
            visited.put(vertex, true); // Đánh dấu đỉnh đã thăm
            DLinkedList<T> outward_vertices = graph->getOutwardEdges(vertex);

            for (T outward_vertex : outward_vertices) {
                if (!visited.get(outward_vertex)) { // Nếu chưa thăm, gọi đệ quy
                    dfsVisit(outward_vertex, dfsVisit);
                }
            }
            vertices_tp_sorted.add(vertex); // Thêm đỉnh vào cuối danh sách khi quay lui
        };

        // Thực hiện DFS trên từng đỉnh chưa thăm
        for (T vertex : vertices_list) {
            if (!visited.get(vertex)) { // Nếu chưa được thăm
                dfsVisit(vertex, dfsVisit);
            }
        }

        // Đảo ngược danh sách trong chính hàm dfsSort
        DLinkedList<T> reversed_list;
        for (auto it = vertices_tp_sorted.bbegin(); it != vertices_tp_sorted.bend(); ++it) {
            reversed_list.add(*it);
        }

        return reversed_list; // Trả về danh sách đã đảo ngược
    }

protected:

    //Helper functions
    XHashMap<T, int> vertex2inDegree(int (*hash)(T&, int));
    XHashMap<T, int> vertex2outDegree(int (*hash)(T&, int));
    DLinkedList<T> listOfZeroInDegrees();

}; //TopoSorter
template<class T>
int TopoSorter<T>::DFS = 0;
template<class T>
int TopoSorter<T>::BFS = 1;

/////////////////////////////End of TopoSorter//////////////////////////////////


#endif /* TOPOSORTER_H */

