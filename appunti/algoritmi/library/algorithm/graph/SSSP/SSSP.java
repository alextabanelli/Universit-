package algorithm.graph.SSSP;

import datastructure.graph.*;
import java.util.Map;

/**
 * Generic graph computation of the shortest paths from a given source vertex
 * @param <D> type of the data object in the graph vertexes
 */
public interface SSSP<D> {

	/**
	 * Generic graph computation of the shortest paths from a given source vertex
	 * @param graph the graph on which the shortest paths must be computed
	 * @param source the initial source vertex
	 * @return the tree of the shortest paths represented as a map from each vertex to the incoming edge in the tree	
	 */	
	public Map<Vertex<D>,Edge<D>> SingleSourceShortestPaths(Graph<D> graph, Vertex<D> source);

}
