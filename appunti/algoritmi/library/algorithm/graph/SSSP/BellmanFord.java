package algorithm.graph.SSSP;

import datastructure.graph.*;
import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;

/**
 * Generic graph computation of the shortest paths from a given source vertex using the Bellman-Ford algorithm
 * @param <D> type of the data object in the graph vertexes
 */	
public class BellmanFord<D> implements SSSP<D> {

	/**
   	 * Constructs a BellmanFord object exposing the SingleSourceShortestPaths method
	 */	
	public BellmanFord() { }
	
	/**
	 * Computes the shortest paths from a given source vertex using the Bellman-Ford algorithm
	 * and returns the tree of the shortes paths represented as a map from each vertex to the 
	 * incoming edge in the tree (returns null if there are negative cycles); Cost: O(n m),
	 * where n and m are respectively the number of vertexes and edges in the graph
	 * @param graph the graph on which the shortest paths must be computed	
	 * @param source the initial source vertex
	 * @return the tree of the shortest paths represented as a map from each vertex to the incoming 
	 *  edge in the tree (null in case of negative cycles)	
	 */	
	public Map<Vertex<D>,Edge<D>> SingleSourceShortestPaths(Graph<D> graph, Vertex<D> source)
	{	
		//strutture dati ausiliarie
		HashMap<Vertex<D>,Double> distance = new HashMap<Vertex<D>,Double>(); //stima della distanza
		HashMap<Vertex<D>,Edge<D>> parent = new HashMap<Vertex<D>,Edge<D>>(); //parent nell'albero dei cammini minimi
		//estrae vertici e archi
		ArrayList<Vertex<D>> vert = graph.vertexes();
		ArrayList<Edge<D>> edge = graph.edges();
		
		//inizializzazione strutture dati
		for(Vertex<D> v : vert)
		{
			distance.put(v, Double.POSITIVE_INFINITY);
			parent.put(v, null);
		}
		
		distance.put(source, 0.0);
		
		for(int c=0;c<graph.vertexNum()-1;c++)
		{
			//effettua n-1 iterazioni di possibili rilassamenti
			for(Edge<D> e : edge)
			{
				//effettua i possibili rilassamenti
				if (distance.get(e.getSource()) + e.getWeight() < distance.get(e.getDest()))
				{
					distance.put(e.getDest(), distance.get(e.getSource()) + e.getWeight());
					parent.put(e.getDest(), e);
				}
			}
		}
		
		//controllo presenza cicli negativi raggiungibili da source
		for(Edge<D> e : edge)
		{
			if (distance.get(e.getSource()) + e.getWeight() < distance.get(e.getDest()))
			{
				return null;
			}
		}
		return parent;
	}


}



