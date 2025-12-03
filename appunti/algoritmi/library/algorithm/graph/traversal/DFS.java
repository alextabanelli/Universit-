package algorithm.graph.traversal;

import datastructure.graph.*;
import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;

/**
 * Implementation of the DFS traversal for graphs containing generic data. Returns an ArrayList of VisitedVertex<D>
 * @param <D> type of the data object in the graph vertexes
 */
public class DFS<D> implements Traversal<D> {
	
	private int time;
	private ArrayList<VisitedVertex<D>> l;
	private Map<Vertex<D>, Boolean> visited;
		
	/**
   	 * Constructs a DFS object exposing the visit method
	 */	
	public DFS() {
		// empty on purpose because there is nothing to initialize
	}
		
	/**
	 * Performs a visit of a passed graph and returns tha ArrayList with the visited vertexes
	 * created as objects of type VisitedVertexDFS<D>
	 * @param graph the graph to visit
	 * @param source the initial source vertex (irrelevant in case of DFS)
	 * @return the ArrayList with the visited vertexes
	 */	
	public ArrayList<VisitedVertex<D>> visit(Graph<D> graph, Vertex<D> source)
	{
		//Inizializzazioni strutture globali
		time = 0;
		l = new ArrayList<VisitedVertex<D>>();
		visited = new HashMap<Vertex<D>, Boolean>();
		ArrayList<Vertex<D>> vert = graph.vertexes(); //Estrae vertici dal grafo
		
		for(int c=0;c<graph.vertexNum();c++)
		{
			Vertex<D> v=vert.get(c);
			visited.put(v, false);
		} //Inizializza marcature
		
		for(int c=0;c<graph.vertexNum();c++)
		{
			Vertex<D> u=vert.get(c);
			
			if (!visited.get(u))
				DFSvisit(graph, new VisitedVertexDFS<D>(u,null)); //u non ha padre
		}
		
		return l;
	}

	/**
	 * Auxiliary function used in the recursive implementation of the DFS visit
	 */
	private void DFSvisit(Graph<D> g, VisitedVertexDFS<D> v)
	{
		visited.put(v.getVertex(),true); //Setta marcatura del vertice visitato
		l.add(v); //Aggiunge il VisitedVertexDFS ricevuto a ArrayList da restituire
		//Setta discovery time
		time++;
		v.dt = time;
		
		for(int c=0;c<g.outDegree(v.getVertex());c++)
		{ //Controlla adiacenze
			Edge<D> e=g.outEdges(v.getVertex()).get(c);
			Vertex<D> w = e.getDest();
			
			if (!visited.get(w)) //Se non ancora marcato visita il vert. adiacente
			DFSvisit(g, new VisitedVertexDFS<D>(w,v.getVertex()));
		}
		
		//Setta finish time
		time++;
		v.ft = time;
	}
}
