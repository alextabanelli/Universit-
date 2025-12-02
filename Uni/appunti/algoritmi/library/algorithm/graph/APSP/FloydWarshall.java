package algorithm.graph.APSP;

import datastructure.graph.*;
import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;

/**
 * Generic graph computation of the shortest path for each pair of source-target vertexes
 * using the Floyd-Warshall algorithm
 * @param <D> type of the data object in the graph vertexes
 */
public class FloydWarshall<D> implements APSP<D> {

	/**
   	 * Constructs a FloydWarshall object exposing the AllPairsShortestPaths method
	 */	
	public FloydWarshall() { }
	
	/**
	 * Computates the shortest paths for each pair of source-target vertexes using the Floyd-Warshall algorithm
	 * and returns the next relation that associates to each pair of source-target vertexes the
	 * first edge in the corresponding shortest path (returns null if there are negative cycles); Cost: O(n<sup>3</sup>),
	 * where n is the number of vertexes in the graph
	 * @param graph the graph on which the shortest paths must be computed
	 * @return a map that associates to each vertex another map associating 
	 * to each target destination the next edge in the corresponding shortest path	
   	 * (null in case of negative cycles)	
	 */	
	public  Map<Vertex<D>, Map<Vertex<D>,Edge<D>>> AllPairsShortestPaths(Graph<D> graph)
	{
		//strutture dati ausiliarie
		HashMap<Vertex<D>, Map<Vertex<D>, Edge<D>>> next = new HashMap<Vertex<D>, Map<Vertex<D>, Edge<D>>>(); //next matrix da restituire
		HashMap<Vertex<D>, Integer> map = new HashMap<Vertex<D>, Integer>(); //associa ad ogni vertici un suo indice
		//estrae vertici e archi
		ArrayList<Vertex<D>> vert = graph.vertexes();
		ArrayList<Edge<D>> edge = graph.edges();
		
		for(int c=0;c<vert.size();c++)
		{
			map.put(vert.get(c), c); //associa ad ogni vertice il suo indice
			next.put(vert.get(c), new HashMap<Vertex<D>,Edge<D>>()); //predispone next matrix
		}
		
		double[][] dist = new double[vert.size()][vert.size()]; //matrice delle distanze
		
		for(int c=0;c<vert.size();c++)
		{
			for(int c2=0;c2<vert.size();c2++)
			{
				if (c==c2) //distanza di un vertice da se stesso uguale a 0
				dist[c][c2] = 0.0;
				else //per indici diversi distanza infinita e nessun cammino per ora trovato
				{
					dist[c][c2] = Double.POSITIVE_INFINITY;
					next.get(vert.get(c)).put(vert.get(c2), null);
				}
			}
		}
		
		for(Edge<D> e : edge)
		{
			//considera cammini costituiti da un solo arco
			dist[map.get(e.getSource())][map.get(e.getDest())] = e.getWeight();
			next.get(e.getSource()).put(e.getDest(),e);
		}
		
		for(int c=0;c<vert.size();c++)
		{
			for(int c2=0;c2<vert.size();c2++)
			{
				for(int c3=0;c3<vert.size();c3++)
				{
					if (dist[c2][c] + dist[c][c3] < dist[c2][c3])
					{
						//cammino migliore grazie a c
						dist[c2][c3] = dist[c2][c] + dist[c][c3]; //aggiorna distanza
						next.get(vert.get(c2)).put(vert.get(c3), next.get(vert.get(c2)).get(vert.get(c))); //aggiorna next
					}
				}
			}
		}
		
		//controllo presenza cicli negativi
		for(int c=0;c<vert.size()-1;c++)
		{
			if (dist[c][c] < 0)
			return null; //ciclo negativo che include vertice con indice x
		}
		
		return next;
	}

}

