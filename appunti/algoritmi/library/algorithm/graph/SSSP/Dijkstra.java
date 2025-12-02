package algorithm.graph.SSSP;

import datastructure.graph.*;
import datastructure.priorityqueue.*;
import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;

/**
 * Generic graph computation of the shortest paths from a given source vertex using the Dijkstra algorithm
 * (it assumes non negative edge weights)
 * @param <D> type of the data object in the graph vertexes
 */	
public class Dijkstra<D> implements SSSP<D> {
	
	/**
   	 * Constructs a Dijkstra object exposing the SingleSourceShortestPaths method
	 */	
	public Dijkstra() { }

	/**
	 * Computes the shortest paths from a given source vertex using the Dijkstra algorithm
	 * and returns the tree of the shortes paths represented as a map from each vertex to the 
	 * incoming edge in the tree (it assumes non negative edge weights); Cost: O(m log n),
	 * where n and m are respectively the number of vertexes and edges in the graph
	 * @param graph the graph on which the shortest paths must be computed	
	 * @param source the initial source vertex
	 * @return the tree of the shortest paths represented as a map from each vertex to the incoming edge in the tree	
	 */	
	public Map<Vertex<D>,Edge<D>> SingleSourceShortestPaths(Graph<D> graph, Vertex<D> source)
	{
		//strutture dati ausiliarie
		DHeap<Double,Vertex<D>> pq = new DHeap<Double,Vertex<D>>(); //struttura priority queue pq
		//mappa da vertici a corrispondenti nodi in pq
		HashMap<Vertex<D>, PriorityQueueNode<Double,Vertex<D>>> pqnodes = new HashMap<Vertex<D>, PriorityQueueNode<Double,Vertex<D>>>();
		HashMap<Vertex<D>, Double> distance = new HashMap<Vertex<D>, Double>(); //distanza dei vertici dall'MST
		HashMap<Vertex<D>, Edge<D>> parent = new HashMap<Vertex<D>, Edge<D>>(); //parent (arco entrante)
		ArrayList<Vertex<D>> vert = graph.vertexes(); //estrae i vertici dal grafo
		
		for(Vertex<D> v : vert)
		{
			distance.put(v,Double.POSITIVE_INFINITY); //inizializza distanza
			parent.put(v, null); //nessun parent identificato
		}
		
		distance.put(source, 0.0); //source a distanza 0 da se stessa
		pqnodes.put(source, pq.insert(0.0,source)); //inserimento source in coda
		
		while (!pq.isEmpty())
		{ //finché ci sono vertici nella coda
			Vertex<D> u = pq.findMin(); pq.deleteMin(); //estrae da pq il vertice da aggiungere
			for(Edge<D> e : graph.outEdges(u))
			{
				//controlla le adiacenze
				Vertex<D> d = e.getDest(); //sia d l'adiacenza da considerare
				if (distance.get(d) == Double.POSITIVE_INFINITY)
				{ //d mai incontrato
					distance.put(d, distance.get(u) + e.getWeight()); //setta distanza
					parent.put(d, e); //indicare il parent momentaneo
					pqnodes.put(d, pq.insert(distance.get(d), d)); //inserisce d in pq
				}
				else if (distance.get(d) > distance.get(u) + e.getWeight())
				{
					//si è trovato un arco migliore per aggiungere v
					distance.put(d, distance.get(u) + e.getWeight()); //aggiorna distanza
					parent.put(d, e); //aggiorna parent
					pq.decreaseKey(distance.get(d), pqnodes.get(d)); //aggiorna chiave in pq
				}
			}
		}
		
			return parent;
	}

}

