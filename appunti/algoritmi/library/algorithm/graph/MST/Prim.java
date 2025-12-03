package algorithm.graph.MST;

import datastructure.graph.*;
import datastructure.priorityqueue.*;
import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;

/**
 * Generic graph computation of the Minimum Spanning Tree using the Prim algorithm
 * @param <D> type of the data object in the graph vertexes
 */	
public class Prim<D> implements MST<D> {
	
	/**
	 * Computes a Minimum Spanning Tree of a passed graph using the Prim algorithm 
	 * and returns the computed spanning tree represented as a graph; Cost: O(m log n),
	 * where n and m are respectively the number of vertexes and edges in the graph
	 * @param graph the graph for which the Minimum Spanning Tree must be computed
	 * @return the graph representing the computed Minimum Spanning Tree
	 */	
	public Graph<D> MinimumSpanningTree(Graph<D> graph)
	{
		//strutture dati ausiliarie
		GraphAL<D> g = new GraphAL<D>(); //grafo per rappresentare il MST da restituire alla fine
		HashMap<Vertex<D>, Vertex<D>> newVert = new HashMap<Vertex<D>, Vertex<D>>(); //mappa tra vecchi e nuovi vert.
		DHeap<Double,Vertex<D>> pq = new DHeap<Double,Vertex<D>>(); //struttura priority queue pq
		//mappa da vertici a corrispondenti nodi in pq
		HashMap<Vertex<D>, PriorityQueueNode<Double,Vertex<D>>> pqnodes = new HashMap<Vertex<D>, PriorityQueueNode<Double,Vertex<D>>>();
		HashMap<Vertex<D>, Boolean> bool = new HashMap<Vertex<D>, Boolean>(); //flag che indica vertice già in MST
		HashMap<Vertex<D>, Double> distance = new HashMap<Vertex<D>, Double>(); //distanza dei vertici dall'MST
		HashMap<Vertex<D>, Vertex<D>> parent = new HashMap<Vertex<D>, Vertex<D>>(); //parent dei vertici
		ArrayList<Vertex<D>> vert = graph.vertexes(); //estrae i vertici dal grafo
		
		for(int c=0;c<graph.vertexNum();c++)
		{
			Vertex<D> v=vert.get(c);
			newVert.put(v, g.addVertex(v.getData())); //nuovo vertice associato a v
			bool.put(v, false); //inizializza flag
			distance.put(v,Double.POSITIVE_INFINITY); //inizializza distanza
		}
		
		Vertex<D> s = vert.get(0); //sceglie vertice di partenza
		pqnodes.put(s, pq.insert(0.0, s)); //inserisce il vertice di partenza nella pq
		
		while (!pq.isEmpty())
		{ //finché ci sono vertici nella coda
			Vertex<D> u = pq.findMin(); //estrae da pq il vertice più vicino all'MST
			pq.deleteMin();
			bool.put(u, true); //setta il flag
			
			if (u != s)
			{ //se il vert. non è la sorg. aggiunge arco da parent (due direz.)
				g.addEdge(newVert.get(parent.get(u)),newVert.get(u),distance.get(u));
				g.addEdge(newVert.get(u),newVert.get(parent.get(u)),distance.get(u));
			}
			
			for(int c=0;c<graph.outDegree(u);c++)
			{ //controlla le adiacenze
				Edge<D> e=graph.outEdges(u).get(c);
				Vertex<D> v = e.getDest(); //sia v l'adiacenza da considerare
				if (distance.get(v) == Double.POSITIVE_INFINITY)
				{ //v mai incontrato
					distance.put(v, e.getWeight()); //setta distanza
					parent.put(v, u); //indicare il parent momentaneo
					pqnodes.put(v, pq.insert(e.getWeight(), v)); //inserisce v in pq
				}
				else if (distance.get(v) > e.getWeight() && !bool.get(v))
				{
					//si è trovato un arco migliore per includere v nell'MST
					distance.put(v, e.getWeight()); //aggiorna distanza
					parent.put(v, u); //aggiorna parent
					pq.decreaseKey( e.getWeight(), pqnodes.get(v)); //aggiorna key in pq
				}
			}
		}
		
		return g;
	}

}

