package algorithm.graph.traversal;

import datastructure.graph.*;

/**
 * Generic vertex returned by a graph DFS visit
 * @param <D> type of the data object in the graph vertexes
 */
public class VisitedVertexDFS<D> extends VisitedVertexBFS<D> {

	/** discovery time */
	protected int dt;

	/** finish time */
	protected int ft;
	
	/**
   	 * Constructs a vertex visited during a DFS
	 * @param visited visited vertex
   	 * @param parent parent of the visited vertex
	 */	
	public VisitedVertexDFS(Vertex<D> visited, Vertex<D> parent) {
		super(visited, parent);
	}
	
	/**
	 * Returns the discovery time of the visited vertex
	 * @return the discovery time of the visited vertex
	 */
	public int getDiscoveryTime () {
		return this.dt;
	}

	/**
	 * Returns the finish time of the visited vertex
	 * @return the finish time of the visited vertex
	 */
	public int getFinishTime () {
		return this.ft;
	}
		
}
