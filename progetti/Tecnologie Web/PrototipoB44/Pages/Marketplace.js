import React from 'react';
import { Link } from 'react-router-dom';
import { createPageUrl } from '../utils';
import { base44 } from '@/api/base44Client';
import { useQuery } from '@tanstack/react-query';
import { Clock, MapPin, ChevronRight, Loader2 } from 'lucide-react';
import { Skeleton } from "@/components/ui/skeleton";

export default function Marketplace() {
  const { data: visits = [], isLoading } = useQuery({
    queryKey: ['visits'],
    queryFn: () => base44.entities.Visit.filter({ is_active: true }),
  });

  return (
    <div className="min-h-screen pb-24">
      {/* Header */}
      <div className="px-4 py-6 max-w-lg mx-auto">
        <h1 className="text-2xl font-bold mb-1">Marketplace Visite</h1>
        <p className="text-slate-400 text-sm">Seleziona una visita per iniziare</p>
      </div>
      
      {/* Visits List */}
      <div className="max-w-lg mx-auto px-4 space-y-4">
        {isLoading ? (
          Array(3).fill(0).map((_, i) => (
            <div key={i} className="glass rounded-2xl overflow-hidden">
              <Skeleton className="h-40 w-full bg-slate-800" />
              <div className="p-4 space-y-2">
                <Skeleton className="h-6 w-3/4 bg-slate-800" />
                <Skeleton className="h-4 w-1/2 bg-slate-800" />
              </div>
            </div>
          ))
        ) : visits.length === 0 ? (
          <div className="glass rounded-2xl p-8 text-center">
            <div className="w-16 h-16 rounded-full bg-slate-800 flex items-center justify-center mx-auto mb-4">
              <MapPin className="w-8 h-8 text-slate-500" />
            </div>
            <h3 className="text-lg font-semibold mb-2">Nessuna visita disponibile</h3>
            <p className="text-slate-400 text-sm">Le visite saranno presto disponibili</p>
          </div>
        ) : (
          visits.map((visit) => (
            <Link 
              key={visit.id} 
              to={createPageUrl(`VisitPlayer?visitId=${visit.id}`)}
              className="block"
            >
              <div className="glass rounded-2xl overflow-hidden hover:bg-slate-800/50 transition-all group">
                <div className="relative h-40">
                  <img 
                    src={visit.cover_image || 'https://images.unsplash.com/photo-1578662996442-48f60103fc96?w=600&q=80'}
                    alt={visit.title}
                    className="w-full h-full object-cover"
                  />
                  <div className="absolute inset-0 bg-gradient-to-t from-slate-950 via-transparent to-transparent" />
                  {visit.duration_minutes && (
                    <div className="absolute top-3 right-3 glass rounded-full px-3 py-1 flex items-center gap-1.5">
                      <Clock className="w-3.5 h-3.5 text-amber-400" />
                      <span className="text-xs font-medium">{visit.duration_minutes} min</span>
                    </div>
                  )}
                </div>
                <div className="p-4">
                  <div className="flex items-start justify-between gap-3">
                    <div>
                      <h2 className="text-lg font-semibold mb-1 group-hover:text-amber-400 transition-colors">
                        {visit.title}
                      </h2>
                      <div className="flex items-center gap-2 text-slate-400 text-sm">
                        <MapPin className="w-4 h-4" />
                        <span>{visit.museum_name}</span>
                      </div>
                      {visit.description && (
                        <p className="text-slate-500 text-sm mt-2 line-clamp-2">
                          {visit.description}
                        </p>
                      )}
                    </div>
                    <ChevronRight className="w-5 h-5 text-slate-500 group-hover:text-amber-400 transition-colors flex-shrink-0 mt-1" />
                  </div>
                </div>
              </div>
            </Link>
          ))
        )}
      </div>
    </div>
  );
}