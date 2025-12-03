package algorithm.graph.traversal;

import datastructure.graph.*;

/**
 * Generic vertex returned by a graph BFS visit
 * @param <D> type of the data object in the graph vertexes
 */
public class VisitedVertexBFS<D> implements VisitedVertex<D> {
	
	/** visited vertex */
	protected Vertex<D> visited;

	/** parent of the visited vertex */
	protected Vertex<D> parent;
	
	/**
   	 * Constructs a visited vertex during a BFS
	 * @param visited visited vertex
   	 * @param parent parent of the visited vertex
	 */	
	public VisitedVertexBFS(Vertex<D> visited, Vertex<D> parent) {
		this.visited = visited;
		this.parent = parent;
	}
	
	/**
	 * Returns the visited vertex
	 * @return the visited vertex
	 */
	public Vertex<D> getVertex () {
		return this.visited;
	}

	/**
	 * Returns the parent of the visited vertex
	 * @return the parent of the visited vertex
	 */
	public Vertex<D> getParent () {
		return this.parent;
	}
	
}
