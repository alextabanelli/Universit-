package algorithm.graph.APSP;

import datastructure.graph.*;
import java.util.Map;

/**
 * Generic graph computation of the shortest path for each pair of source-target vertexes
 * @param <D> type of the data object in the graph vertexes
 */
public interface APSP<D> {
	
	/**
	 * Generic graph computation of the shortest paths for each pair of source-target vertexes
	 * @param graph the graph on which the shortest paths must be computed
	 * @return a map that associates to each vertex another map associating 
	 * to each target destination the next edge in the corresponding shortest path	
	 * (null in case of negative cycles)	
	 */	
	public Map<Vertex<D>, Map<Vertex<D>,Edge<D>>> AllPairsShortestPaths(Graph<D> graph);
	
}
