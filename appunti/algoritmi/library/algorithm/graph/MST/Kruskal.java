package algorithm.graph.MST;

import datastructure.graph.*;
import datastructure.unionfind.*;
import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;
import java.util.Comparator;

/**
 * Generic graph computation of the Minimum Spanning Tree using the Kruskal algorithm
 * @param <D> type of the data object in the graph vertexes
 */
public class Kruskal<D> implements MST<D> {

	/**
	 * Computes a Minimum Spanning Tree of a passed graph using the Kruskal algorithm 
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
		QuickUnionRank<D> uf = new QuickUnionRank<D>(); //struttura union find uf
		HashMap<Vertex<D>, UnionFindNode<D>> ufnodes = new HashMap<Vertex<D>, UnionFindNode<D>>(); //mappa da vert. a set in uf
		
		for(int c=0;c<graph.vertexNum();c++)
		{
			Vertex<D> v=graph.vertexes().get(c);
			newVert.put(v, g.addVertex(v.getData())); //nuovo vertice associato a v
			ufnodes.put(v, uf.makeSet(v.getData())); //singoletto in uf associato a v
		}
		
		ArrayList<Edge<D>> e = graph.edges(); //estrae gli archi dal grafo
		e.sort(new CompEdge()); //ordina gli archi usando specifico comparator per archi
		
		for(int c=0;c<graph.edgeNum();c++)
		{
			Edge<D> edge=e.get(c);
			Vertex<D> u = edge.getSource();
			Vertex<D> v = edge.getDest();
			Double w = edge.getWeight();
			UnionFindNode<D> ru = uf.find(ufnodes.get(u)); //rappresentante del set della sorgente
			UnionFindNode<D> rv = uf.find(ufnodes.get(v)); //rappresentante del set della destinazione
			
			if (ru != rv)
			{ //set disgiunti quindi l'arco deve essere selezionato
				uf.union(ru, rv); //unisce i set di sorgente e destinazione
				g.addEdge(newVert.get(u),newVert.get(v),w); //aggiunge arco in g
				g.addEdge(newVert.get(v),newVert.get(u),w); //in entrambe le direzioni
			}
		}
		
		return g;
	}
	
	/**
	 * The comparator used for sorting the edges of the graph
	 */	
	private class CompEdge implements Comparator<Edge<D>> {
		public int compare(Edge<D> e1, Edge<D> e2) {
			if (e1.getWeight() > e2.getWeight())
				return 1; 
			else
				return -1;
		}
	}

}
