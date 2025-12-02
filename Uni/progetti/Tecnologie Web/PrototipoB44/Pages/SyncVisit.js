import React, { useState, useEffect, useCallback } from 'react';
import { useNavigate } from 'react-router-dom';
import { createPageUrl } from '../utils';
import { base44 } from '@/api/base44Client';
import { useQuery } from '@tanstack/react-query';
import { 
  ArrowLeft, 
  Map, 
  Accessibility, 
  Users,
  Loader2,
  Image as ImageIcon,
  Radio,
  Lock
} from 'lucide-react';
import { Button } from "@/components/ui/button";
import { toast } from "sonner";
import AudioPlayer from '../components/visit/AudioPlayer';
import VoiceCommands from '../components/visit/VoiceCommands';
import MuseumMap from '../components/visit/MuseumMap';

export default function SyncVisit() {
  const navigate = useNavigate();
  const urlParams = new URLSearchParams(window.location.search);
  const sessionId = urlParams.get('sessionId');
  
  const [accessible, setAccessible] = useState(false);
  const [showMap, setShowMap] = useState(false);
  const [descriptionLevel, setDescriptionLevel] = useState('standard');
  const [highlightedFacility, setHighlightedFacility] = useState(null);
  const [currentText, setCurrentText] = useState('');

  // Poll session for updates
  const { data: session, isLoading: sessionLoading } = useQuery({
    queryKey: ['session', sessionId],
    queryFn: async () => {
      const sessions = await base44.entities.Session.filter({ id: sessionId });
      return sessions[0];
    },
    enabled: !!sessionId,
    refetchInterval: 2000, // Poll every 2 seconds
  });

  const { data: visit } = useQuery({
    queryKey: ['visit', session?.visit_id],
    queryFn: async () => {
      const visits = await base44.entities.Visit.filter({ id: session.visit_id });
      return visits[0];
    },
    enabled: !!session?.visit_id,
  });

  const { data: artworks = [] } = useQuery({
    queryKey: ['artworks', session?.visit_id],
    queryFn: () => base44.entities.Artwork.filter({ visit_id: session.visit_id }),
    enabled: !!session?.visit_id,
  });

  const currentIndex = session?.current_artwork_index || 0;
  const currentArtwork = artworks[currentIndex];

  // Check for quiz mode
  useEffect(() => {
    if (session?.status === 'quiz') {
      navigate(createPageUrl(`Quiz?sessionId=${sessionId}`));
    }
  }, [session?.status, sessionId, navigate]);

  useEffect(() => {
    if (currentArtwork) {
      updateDescription(descriptionLevel);
    }
  }, [currentArtwork, descriptionLevel]);

  const updateDescription = (level) => {
    if (!currentArtwork?.descriptions) {
      setCurrentText(currentArtwork?.descriptions?.standard || 'Descrizione non disponibile');
      return;
    }
    const desc = currentArtwork.descriptions[level] || currentArtwork.descriptions.standard || '';
    setCurrentText(desc);
  };

  // Limited commands for synchronized visit
  const handleCommand = useCallback((command, transcript) => {
    switch (command) {
      case 'next':
      case 'previous':
        toast.info('Navigazione controllata dal docente');
        break;
        
      case 'more':
        setDescriptionLevel('detailed');
        toast.info('Descrizione dettagliata');
        break;
        
      case 'less':
        setDescriptionLevel('brief');
        toast.info('Descrizione breve');
        break;
        
      case 'simpler':
        setDescriptionLevel('simple');
        toast.info('Descrizione semplificata');
        break;
        
      case 'exit':
      case 'toilet':
      case 'bar':
      case 'shop':
        setHighlightedFacility(command);
        setShowMap(true);
        break;
        
      default:
        toast.info('Comando non disponibile in modalità sincronizzata');
    }
  }, []);

  // Commands disabled in sync mode
  const disabledCommands = ['next', 'previous', 'whatIsThis', 'author', 'style'];

  if (sessionLoading) {
    return (
      <div className="min-h-screen flex items-center justify-center">
        <Loader2 className="w-10 h-10 text-violet-500 animate-spin" />
      </div>
    );
  }

  if (!session) {
    return (
      <div className="min-h-screen flex flex-col items-center justify-center p-4">
        <p className="text-slate-400 mb-4">Sessione non trovata</p>
        <Button onClick={() => navigate(createPageUrl('JoinSession'))} className="bg-violet-600 hover:bg-violet-700">
          Torna indietro
        </Button>
      </div>
    );
  }

  return (
    <div className="min-h-screen bg-slate-950 flex flex-col">
      {/* Header */}
      <header className="glass border-b border-slate-800 p-3">
        <div className="flex items-center justify-between max-w-lg mx-auto">
          <Button 
            variant="ghost" 
            size="icon"
            onClick={() => navigate(createPageUrl('JoinSession'))}
          >
            <ArrowLeft className="w-5 h-5" />
          </Button>
          
          <div className="text-center flex-1 px-4">
            <div className="flex items-center justify-center gap-2">
              <Radio className="w-4 h-4 text-green-500 animate-pulse" />
              <span className="text-xs font-medium text-green-500 uppercase tracking-wider">
                Sincronizzato
              </span>
            </div>
            <h1 className="font-semibold text-sm truncate">{visit?.title || 'Sessione'}</h1>
          </div>
          
          <div className="flex items-center gap-1">
            <Button 
              variant="ghost" 
              size="icon"
              onClick={() => setShowMap(true)}
            >
              <Map className="w-5 h-5" />
            </Button>
            <Button 
              variant={accessible ? 'default' : 'ghost'}
              size="icon"
              onClick={() => setAccessible(!accessible)}
              className={accessible ? 'bg-violet-500 text-white' : ''}
            >
              <Accessibility className="w-5 h-5" />
            </Button>
          </div>
        </div>
      </header>
      
      {/* Sync Status Bar */}
      <div className="bg-violet-900/30 border-b border-violet-500/30 px-4 py-2">
        <div className="max-w-lg mx-auto flex items-center justify-between text-sm">
          <div className="flex items-center gap-2">
            <Users className="w-4 h-4 text-violet-400" />
            <span className="text-violet-300">Sessione: {session.mnemonic_code}</span>
          </div>
          <span className="text-violet-400">{currentIndex + 1} / {artworks.length}</span>
        </div>
      </div>
      
      {/* Progress Bar */}
      <div className="h-1 bg-slate-800">
        <div 
          className="h-full bg-violet-500 transition-all duration-500"
          style={{ width: `${((currentIndex + 1) / Math.max(artworks.length, 1)) * 100}%` }}
        />
      </div>
      
      {/* Main Content */}
      <div className="flex-1 overflow-auto">
        <div className="max-w-lg mx-auto p-4 space-y-4">
          {/* Waiting State */}
          {session.status === 'waiting' && (
            <div className="glass rounded-2xl p-8 text-center">
              <Loader2 className="w-12 h-12 text-violet-500 animate-spin mx-auto mb-4" />
              <h2 className="text-xl font-semibold mb-2">In attesa del docente...</h2>
              <p className="text-slate-400 text-sm">
                La visita inizierà quando il docente avvierà la sessione
              </p>
            </div>
          )}
          
          {/* Active State */}
          {session.status === 'active' && currentArtwork && (
            <>
              {/* Artwork Image */}
              <div className="relative aspect-[4/3] rounded-2xl overflow-hidden bg-slate-800">
                {currentArtwork.image_url ? (
                  <img 
                    src={currentArtwork.image_url} 
                    alt={currentArtwork.title}
                    className="w-full h-full object-cover"
                  />
                ) : (
                  <div className="w-full h-full flex items-center justify-center">
                    <ImageIcon className="w-16 h-16 text-slate-600" />
                  </div>
                )}
                <div className="absolute bottom-0 left-0 right-0 p-4 bg-gradient-to-t from-slate-950">
                  <h2 className={`font-bold ${accessible ? 'text-2xl' : 'text-xl'}`}>
                    {currentArtwork.title}
                  </h2>
                  {currentArtwork.author && (
                    <p className={`text-violet-400 ${accessible ? 'text-lg' : 'text-sm'}`}>
                      {currentArtwork.author}
                      {currentArtwork.year && ` • ${currentArtwork.year}`}
                    </p>
                  )}
                </div>
              </div>
              
              {/* Description */}
              <div className={`glass rounded-2xl p-4 ${accessible ? 'text-lg leading-relaxed' : 'text-sm'}`}>
                <p className="text-slate-300">{currentText}</p>
              </div>
              
              {/* Audio Player */}
              <AudioPlayer text={currentText} accessible={accessible} />
              
              {/* Limited Commands */}
              <div className="glass rounded-2xl p-4">
                <div className="flex items-center gap-2 mb-4 text-sm text-slate-400">
                  <Lock className="w-4 h-4" />
                  <span>Navigazione controllata dal docente</span>
                </div>
                
                <div className={`grid ${accessible ? 'grid-cols-2 gap-3' : 'grid-cols-4 gap-2'}`}>
                  {[
                    { id: 'more', label: 'Dimmi di più', color: 'bg-emerald-600' },
                    { id: 'less', label: 'Dimmi di meno', color: 'bg-orange-600' },
                    { id: 'simpler', label: 'Più semplice', color: 'bg-purple-600' },
                  ].map((btn) => (
                    <Button
                      key={btn.id}
                      onClick={() => handleCommand(btn.id)}
                      className={`${btn.color} hover:opacity-90 ${
                        accessible ? 'h-16 text-lg' : 'h-12 text-sm'
                      } rounded-xl`}
                    >
                      {btn.label}
                    </Button>
                  ))}
                </div>
              </div>
            </>
          )}
        </div>
      </div>
      
      {/* Voice Command Button */}
      <div className="fixed bottom-6 right-6">
        <VoiceCommands 
          onCommand={handleCommand} 
          disabledCommands={disabledCommands}
        />
      </div>
      
      {/* Map Modal */}
      {showMap && (
        <MuseumMap
          mapLayout={visit?.map_layout}
          artworks={artworks}
          currentArtworkId={currentArtwork?.id}
          onClose={() => {
            setShowMap(false);
            setHighlightedFacility(null);
          }}
          highlightedFacility={highlightedFacility}
        />
      )}
    </div>
  );
}