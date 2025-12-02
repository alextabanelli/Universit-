import React from 'react';
import { Link } from 'react-router-dom';
import { createPageUrl } from '../utils';
import { Map, Users, Compass, Sparkles } from 'lucide-react';
import { Button } from "@/components/ui/button";

export default function Home() {
  return (
    <div className="min-h-screen pb-24">
      {/* Hero Section */}
      <div className="relative h-72 overflow-hidden">
        <img 
          src="https://images.unsplash.com/photo-1564399579883-451a5d44ec08?w=800&q=80" 
          alt="Museum"
          className="w-full h-full object-cover"
        />
        <div className="absolute inset-0 bg-gradient-to-t from-slate-950 via-slate-950/60 to-transparent" />
        <div className="absolute bottom-0 left-0 right-0 p-6">
          <div className="max-w-lg mx-auto">
            <h1 className="text-3xl font-bold mb-2">
              <span className="text-amber-400">Art</span>Around Navigator
            </h1>
            <p className="text-slate-300 text-sm">
              Esplora musei con guide audio interattive
            </p>
          </div>
        </div>
      </div>
      
      {/* Main Actions */}
      <div className="max-w-lg mx-auto px-4 py-8 space-y-4">
        <Link to={createPageUrl('Marketplace')} className="block">
          <div className="glass rounded-2xl p-6 hover:bg-slate-800/50 transition-all group">
            <div className="flex items-start gap-4">
              <div className="w-14 h-14 rounded-xl btn-accent flex items-center justify-center flex-shrink-0">
                <Compass className="w-7 h-7 text-slate-900" />
              </div>
              <div className="flex-1">
                <h2 className="text-xl font-semibold mb-1 group-hover:text-amber-400 transition-colors">
                  Esplora Visite
                </h2>
                <p className="text-slate-400 text-sm">
                  Scopri le visite disponibili e inizia la tua esplorazione autonoma
                </p>
              </div>
            </div>
          </div>
        </Link>
        
        <Link to={createPageUrl('JoinSession')} className="block">
          <div className="glass rounded-2xl p-6 hover:bg-slate-800/50 transition-all group">
            <div className="flex items-start gap-4">
              <div className="w-14 h-14 rounded-xl bg-gradient-to-br from-violet-500 to-purple-600 flex items-center justify-center flex-shrink-0">
                <Users className="w-7 h-7 text-white" />
              </div>
              <div className="flex-1">
                <h2 className="text-xl font-semibold mb-1 group-hover:text-violet-400 transition-colors">
                  Unisciti a Sessione
                </h2>
                <p className="text-slate-400 text-sm">
                  Partecipa a una visita guidata sincronizzata con il docente
                </p>
              </div>
            </div>
          </div>
        </Link>
        
        {/* Features */}
        <div className="pt-6">
          <h3 className="text-sm font-medium text-slate-500 uppercase tracking-wider mb-4 px-2">
            Funzionalità
          </h3>
          <div className="grid grid-cols-2 gap-3">
            {[
              { icon: Map, label: 'Mappa Interattiva', color: 'text-emerald-400' },
              { icon: Sparkles, label: 'Audio Guide', color: 'text-amber-400' },
            ].map((feature, i) => (
              <div key={i} className="glass rounded-xl p-4 text-center">
                <feature.icon className={`w-6 h-6 mx-auto mb-2 ${feature.color}`} />
                <span className="text-sm text-slate-300">{feature.label}</span>
              </div>
            ))}
          </div>
        </div>
        
        {/* Accessible Mode Info */}
        <div className="glass rounded-2xl p-4 mt-6 border border-amber-500/30">
          <div className="flex items-center gap-3">
            <div className="w-10 h-10 rounded-lg bg-amber-500/20 flex items-center justify-center">
              <span className="text-2xl">♿</span>
            </div>
            <div>
              <p className="font-medium text-amber-400">Modalità Accessibile</p>
              <p className="text-xs text-slate-400">Attivabile durante la visita con pulsanti grandi</p>
            </div>
          </div>
        </div>
      </div>
    </div>
  );
}