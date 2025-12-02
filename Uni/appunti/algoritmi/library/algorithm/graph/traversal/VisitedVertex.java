package algorithm.graph.traversal;

import datastructure.graph.*;

/**
 * Generic vertex returned by a graph visit
 * @param <D> type of the data object in the graph vertexes
 */
public interface VisitedVertex<D> {
	
	/**
	 * Returns the visited vertex 
	 * @return the visited vertex
	 */
	public Vertex<D> getVertex();
	
}
