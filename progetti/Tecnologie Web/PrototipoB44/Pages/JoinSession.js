import React, { useState } from 'react';
import { useNavigate } from 'react-router-dom';
import { createPageUrl } from '../utils';
import { base44 } from '@/api/base44Client';
import { Users, Loader2, ArrowRight } from 'lucide-react';
import { Button } from "@/components/ui/button";
import { Input } from "@/components/ui/input";
import { toast } from "sonner";

export default function JoinSession() {
  const navigate = useNavigate();
  const [code, setCode] = useState('');
  const [loading, setLoading] = useState(false);

  const handleJoin = async () => {
    if (!code.trim()) {
      toast.error('Inserisci il codice della sessione');
      return;
    }

    setLoading(true);
    
    try {
      // Find session by mnemonic code
      const sessions = await base44.entities.Session.filter({ 
        mnemonic_code: code.trim(),
        status: 'active'
      });
      
      if (sessions.length === 0) {
        // Also check for waiting sessions
        const waitingSessions = await base44.entities.Session.filter({ 
          mnemonic_code: code.trim(),
          status: 'waiting'
        });
        
        if (waitingSessions.length === 0) {
          toast.error('Sessione non trovata o non attiva');
          setLoading(false);
          return;
        }
        
        // Join waiting session
        const session = waitingSessions[0];
        navigate(createPageUrl(`SyncVisit?sessionId=${session.id}`));
      } else {
        const session = sessions[0];
        navigate(createPageUrl(`SyncVisit?sessionId=${session.id}`));
      }
    } catch (error) {
      console.error('Error joining session:', error);
      toast.error('Errore nel partecipare alla sessione');
    } finally {
      setLoading(false);
    }
  };

  return (
    <div className="min-h-screen pb-24">
      {/* Hero */}
      <div className="relative h-48 overflow-hidden">
        <img 
          src="https://images.unsplash.com/photo-1580060839134-75a5edca2e99?w=800&q=80" 
          alt="Museum Tour"
          className="w-full h-full object-cover"
        />
        <div className="absolute inset-0 bg-gradient-to-t from-slate-950 via-slate-950/70 to-transparent" />
        <div className="absolute bottom-0 left-0 right-0 p-6">
          <div className="max-w-lg mx-auto">
            <h1 className="text-2xl font-bold">Unisciti a una Sessione</h1>
            <p className="text-slate-400 text-sm mt-1">
              Partecipa a una visita guidata sincronizzata
            </p>
          </div>
        </div>
      </div>
      
      <div className="max-w-lg mx-auto px-4 py-8">
        {/* Join Card */}
        <div className="glass rounded-2xl p-6">
          <div className="w-16 h-16 rounded-2xl bg-gradient-to-br from-violet-500 to-purple-600 flex items-center justify-center mx-auto mb-6">
            <Users className="w-8 h-8 text-white" />
          </div>
          
          <h2 className="text-xl font-semibold text-center mb-2">
            Codice Sessione
          </h2>
          <p className="text-slate-400 text-sm text-center mb-6">
            Inserisci il codice mnemonico fornito dal docente
          </p>
          
          <div className="space-y-4">
            <Input
              value={code}
              onChange={(e) => setCode(e.target.value)}
              placeholder="es. Fenice Rossa"
              className="h-14 text-lg text-center bg-slate-800 border-slate-700 rounded-xl"
              onKeyDown={(e) => e.key === 'Enter' && handleJoin()}
            />
            
            <Button
              onClick={handleJoin}
              disabled={loading}
              className="w-full h-14 text-lg font-semibold rounded-xl bg-gradient-to-r from-violet-500 to-purple-600 hover:from-violet-600 hover:to-purple-700"
            >
              {loading ? (
                <Loader2 className="w-5 h-5 animate-spin" />
              ) : (
                <>
                  Partecipa
                  <ArrowRight className="w-5 h-5 ml-2" />
                </>
              )}
            </Button>
          </div>
        </div>
        
        {/* Info */}
        <div className="mt-6 glass rounded-2xl p-4">
          <h3 className="font-medium mb-3 text-sm text-slate-400 uppercase tracking-wider">
            Come funziona
          </h3>
          <ul className="space-y-3 text-sm text-slate-300">
            <li className="flex items-start gap-3">
              <span className="w-6 h-6 rounded-full bg-violet-500/20 text-violet-400 flex items-center justify-center flex-shrink-0 text-xs font-bold">1</span>
              <span>Il docente condivide un codice mnemonico</span>
            </li>
            <li className="flex items-start gap-3">
              <span className="w-6 h-6 rounded-full bg-violet-500/20 text-violet-400 flex items-center justify-center flex-shrink-0 text-xs font-bold">2</span>
              <span>Inserisci il codice per unirti alla visita</span>
            </li>
            <li className="flex items-start gap-3">
              <span className="w-6 h-6 rounded-full bg-violet-500/20 text-violet-400 flex items-center justify-center flex-shrink-0 text-xs font-bold">3</span>
              <span>Segui la visita sincronizzata con il gruppo</span>
            </li>
            <li className="flex items-start gap-3">
              <span className="w-6 h-6 rounded-full bg-violet-500/20 text-violet-400 flex items-center justify-center flex-shrink-0 text-xs font-bold">4</span>
              <span>Completa il quiz finale per verificare l'apprendimento</span>
            </li>
          </ul>
        </div>
      </div>
    </div>
  );
}