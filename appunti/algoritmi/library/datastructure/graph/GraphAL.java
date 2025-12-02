package datastructure.graph;

import java.util.ArrayList;
import java.util.List;
import java.util.LinkedList;
import java.util.Iterator;

/**
 * Implementation using Adjacent Lists of a generic Graph data structure composed of vertexes 
 * of type VertexAL containing <code>data</code> objects and edges of type EdgeAL
 * @param <D> type of the data object
 */
public class GraphAL<D> implements Graph<D> {

	/** number of vertexes */
	protected int n;
	
	/** number of edges */
	protected int m;
	
	/** list of vertexes */
	protected ArrayList<VertexAL<D>> vertexes;

	/**
   	 * Constructs an empty graph implementated using adjacent lists; Cost: O(1)
	 */		
	public GraphAL(){
		n = 0;
		m = 0;
		vertexes = new ArrayList<VertexAL<D>>();
	}
	
	/**
	 * Returns the number of vertexes of the graph; Cost: O(1)
	 * @return the number of vertexes
	 */
	public int vertexNum() { return n; }

	/**
	 * Returns the number of edges of the graph; Cost: O(1)
	 * @return the number of edges
	 */
	public int edgeNum() { return m; }

	/**
	 * Returns a list with the vertexes currently in the graph; 
	 * Cost: &Theta;(n), where n is the number of vertexes in the graph
	 * @return a list with the vertexes currently in the graph
	 */
	public ArrayList<Vertex<D>> vertexes()
	{ 
		ArrayList<Vertex<D>> V = new ArrayList<Vertex<D>>();
		
		for(int c=0;c<n;c++)
		{
			V.add(vertexes.get(c));
		}
		
		return V;
	}
	
	/**
	 * Returns a list with the edges currently in the graph; 
	 * Cost &Theta;(m), where m is the number of edges in the graph
	 * @return the list with the edges currently in the graph
	 */	
	public ArrayList<Edge<D>> edges()
	{
		ArrayList<Edge<D>> E = new ArrayList<Edge<D>>();

		for (int c=0;c<n;c++)
		{
			Iterator<EdgeAL<D>> it = (vertexes.get(c)).adjac.iterator();
			while (it.hasNext())
			{ 
				E.add(it.next());
			}					
		}
		
		return E;
	}

	/**
	 * Returns the out degree of a vertex; Cost: O(1)
     * @param v vertex
	 * @return the out degree of the vertex <code>v</code>
	 */	
	public int outDegree(Vertex<D> v)
	{
		return ((VertexAL)v).adjac.size();
	}
	
	/**
	 * Returns a list with the edges currently exiting from a given vertex; 
	 * Cost: O(&delta;v), where  &delta;v is the out degree of v
     * @param v vertex
	 * @return the list of edges exiting from the vertex <code>v</code>
	 */	
	public ArrayList<Edge<D>> outEdges(Vertex<D> v)
	{
		Edge<D> tmp;
		ArrayList<Edge<D>> E=new ArrayList<Edge<D>>();
		
		for (int c=0;c<n;c++)
		{
			Iterator<EdgeAL<D>> it = (vertexes.get(c)).adjac.iterator();
			while (it.hasNext())
			{ 
				tmp=it.next();
				if(tmp.getSource()==v)
					E.add(tmp);
			}					
		}
		
		return E;
	}
	
	/**
	 * Returns the edge connecting two given vertexes
	 * (returns null if the edge does not exist);
	 * Cost: O(&delta;x), where  &delta;x is the out degree of x
     * <ul>
     * <li> Worst-case: &Theta;(&delta;x)
     * <li> Best-case: O(1) 
     * </ul>	
     * @param x source vertex
     * @param y destination vertex
	 * @return the edge connecting <code>x</code> and <code>y</code> (return null if 
	 * <code>x</code> and <code>y</code> are not connected)
	 */	
	public Edge<D> areAdjacent(Vertex<D> x, Vertex<D> y)
	{
		Iterator<EdgeAL<D>> it = ((VertexAL)x).adjac.iterator();
		while (it.hasNext())
		{ 
			EdgeAL<D>E = it.next();
			if (E.getDest() == y)
			{
				return E;
			}
		}

		return null;
	}

	/**
	 * Add a vertex to the graph; Cost: O(1)
     * @param data the datum to insert in the new vertex
	 * @return the new vertex
	 */	
	public Vertex<D> addVertex(D data)
	{
		VertexAL<D> V=new VertexAL<D>(data);
		
		vertexes.add(V);
		n++;

		return V;
	}

	/**
	 * Add an edge to the graph; Cost: O(1)
     * @param source the source of the edge to add
     * @param dest the destination of the edge to add	
	 */	
	public void addEdge(Vertex<D> source, Vertex<D> dest)
	{
		VertexAL<D> S=(VertexAL) source;
		VertexAL<D> D=(VertexAL) dest;
		EdgeAL<D> E=new EdgeAL<D>(S,D);
		
		S.adjac.add(E);
		m++;
	}

	/**
	 * Add an edge to the graph; Cost: O(1)
     * @param source the source of the edge to add
     * @param dest the destination of the edge to add	
     * @param weight the weight of the edge to add	
	 */		
	public void addEdge(Vertex<D> source, Vertex<D> dest, double weight)
	{
		VertexAL<D> S=(VertexAL) source;
		VertexAL<D> D=(VertexAL) dest;
		EdgeAL<D> E=new EdgeAL<D>(S,D,weight);
		
		S.adjac.add(E);
		m++;
	}
	
	/**
	 * Remove a vertex; 
	 * Cost &Theta;(n+m), where n is the number of vertexes in the graph
	 * and m is the number of edges in the graph
     * @param v the vertex to remove
	 */	
	public void removeVertex(Vertex<D> v) {
		VertexAL<D> vAL = (VertexAL<D>)v;
		int index = 0;
		while (index < n && vertexes.get(index) != v) index++;
		if (index == n) return;
		if (index == n-1) {
			vertexes.remove(index);
		} else {
			VertexAL<D> vert = vertexes.remove(n-1);
			vertexes.set(index,vert);
		}
		n = n - 1;
		m = m - vAL.adjac.size();
		Edge<D> e;
		for (int i=0; i<n; i++)
		{
			Iterator<EdgeAL<D>> it = (vertexes.get(i)).adjac.iterator();
			while (it.hasNext())
			{ 
				e = it.next();
				if (e.getDest() == v)
				{
					it.remove();
					m = m - 1;
				}
			}					
		}
	}

	/**
	 * Remove an edge; Cost: O(&delta;e.source), where  &delta;e.source is the out degree of 
	 * the source vertex of the edge to remove
     * <ul>
     * <li> Worst-case: &Theta;(&delta;e.source)
     * <li> Best-case: O(1) 
     * </ul>
     * @param e the edge to remove
	 */	
	public void removeEdge(Edge<D> e)
	{
		VertexAL<D> V=(VertexAL<D>)e.getSource();
		
		Iterator<EdgeAL<D>> it = V.adjac.iterator();
		Edge<D> tmp;
		
		while(it.hasNext())
		{
			tmp=it.next();
			
			if(tmp.getDest()==e.getDest())
			{
				it.remove();
				m--;
			}
		}
	}
	
	/**
	 * Returns a printable string representation of the Graph. For each vertex
     * in the graph lists the adjacent vertexes; 
	 * Cost &Theta;(n+m), where n is the number of vertexes in the graph
	 * and m is the number of edges in the graph
	 * @return string representation of the Graph
	 */
	@Override
	public String toString() {
		String S = "";
		for (int i=0; i<n; i++) {
			VertexAL<D> v = vertexes.get(i);
			S = S + v.getData().toString() + "\n";
			for (int j=0; j<v.adjac.size(); j++) {
				if (j<v.adjac.size()-1)
					S = S+"├──── ";
				else
					S = S+"└──── ";
				S = S+v.adjac.get(j).getDest().getData().toString()+"\n";
			}
		}
		return S;
	}

}
