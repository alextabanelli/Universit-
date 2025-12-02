package algorithm.graph.traversal;

import datastructure.graph.*;
import java.util.ArrayList;

/**
 * Generic graph traversal interface that returns an ArrayList of VisitedVertex<D>
 * @param <D> type of the data object in the graph vertexes
 */
public interface Traversal<D> {

	/**
	 * Performs a visit of a passed graph and returns the ArrayList with the visited vertexes
	 * @param graph the graph to visit
	 * @param source the initial source vertex (irrelevant in case of DFS)
	 * @return the ArrayList with the visited vertexes
	 */	
	public ArrayList<VisitedVertex<D>> visit(Graph<D> graph, Vertex<D> source);

}