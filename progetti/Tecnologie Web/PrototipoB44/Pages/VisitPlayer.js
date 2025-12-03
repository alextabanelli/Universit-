import React, { useState, useEffect, useCallback } from 'react';
import { useNavigate } from 'react-router-dom';
import { createPageUrl } from '../utils';
import { base44 } from '@/api/base44Client';
import { useQuery } from '@tanstack/react-query';
import { 
  ArrowLeft, 
  Map, 
  Accessibility, 
  ChevronLeft, 
  ChevronRight,
  Loader2,
  Image as ImageIcon
} from 'lucide-react';
import { Button } from "@/components/ui/button";
import { toast } from "sonner";
import AudioPlayer from '../components/visit/AudioPlayer';
import CommandButtons from '../components/visit/CommandButtons';
import VoiceCommands from '../components/visit/VoiceCommands';
import MuseumMap from '../components/visit/MuseumMap';

export default function VisitPlayer() {
  const navigate = useNavigate();
  const urlParams = new URLSearchParams(window.location.search);
  const visitId = urlParams.get('visitId');
  
  const [currentIndex, setCurrentIndex] = useState(0);
  const [accessible, setAccessible] = useState(false);
  const [showMap, setShowMap] = useState(false);
  const [descriptionLevel, setDescriptionLevel] = useState('standard');
  const [highlightedFacility, setHighlightedFacility] = useState(null);
  const [currentText, setCurrentText] = useState('');

  const { data: visit, isLoading: visitLoading } = useQuery({
    queryKey: ['visit', visitId],
    queryFn: () => base44.entities.Visit.filter({ id: visitId }),
    enabled: !!visitId,
    select: (data) => data[0],
  });

  const { data: artworks = [], isLoading: artworksLoading } = useQuery({
    queryKey: ['artworks', visitId],
    queryFn: () => base44.entities.Artwork.filter({ visit_id: visitId }),
    enabled: !!visitId,
  });

  const currentArtwork = artworks[currentIndex];

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

  const handleCommand = useCallback((command, transcript) => {
    switch (command) {
      case 'next':
        if (currentIndex < artworks.length - 1) {
          setCurrentIndex(prev => prev + 1);
          setDescriptionLevel('standard');
          toast.success('Opera successiva');
        } else {
          toast.info('Sei all\'ultima opera');
        }
        break;
        
      case 'previous':
        if (currentIndex > 0) {
          setCurrentIndex(prev => prev - 1);
          setDescriptionLevel('standard');
          toast.success('Opera precedente');
        } else {
          toast.info('Sei alla prima opera');
        }
        break;
        
      case 'whatIsThis':
        if (currentArtwork) {
          setCurrentText(`Questa è "${currentArtwork.title}" di ${currentArtwork.author || 'autore sconosciuto'}.`);
        }
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
        
      case 'author':
        if (currentArtwork?.author) {
          setCurrentText(`L'autore di questa opera è ${currentArtwork.author}. ${currentArtwork.year ? `È stata realizzata nel ${currentArtwork.year}.` : ''}`);
        } else {
          setCurrentText('Autore non disponibile per questa opera.');
        }
        break;
        
      case 'style':
        if (currentArtwork?.style) {
          setCurrentText(`Questa opera appartiene allo stile ${currentArtwork.style}.`);
        } else {
          setCurrentText('Informazioni sullo stile non disponibili.');
        }
        break;
        
      case 'exit':
      case 'toilet':
      case 'bar':
      case 'shop':
        setHighlightedFacility(command);
        setShowMap(true);
        toast.info(`Mostrando ${command} sulla mappa`);
        break;
    }
  }, [currentIndex, artworks, currentArtwork]);

  if (visitLoading || artworksLoading) {
    return (
      <div className="min-h-screen flex items-center justify-center">
        <Loader2 className="w-10 h-10 text-amber-500 animate-spin" />
      </div>
    );
  }

  if (!visit) {
    return (
      <div className="min-h-screen flex flex-col items-center justify-center p-4">
        <p className="text-slate-400 mb-4">Visita non trovata</p>
        <Button onClick={() => navigate(createPageUrl('Marketplace'))} className="btn-accent">
          Torna al Marketplace
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
            onClick={() => navigate(createPageUrl('Marketplace'))}
          >
            <ArrowLeft className="w-5 h-5" />
          </Button>
          
          <div className="text-center flex-1 px-4">
            <h1 className="font-semibold text-sm truncate">{visit.title}</h1>
            <p className="text-xs text-slate-400">{currentIndex + 1} / {artworks.length}</p>
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
              className={accessible ? 'bg-amber-500 text-slate-900' : ''}
            >
              <Accessibility className="w-5 h-5" />
            </Button>
          </div>
        </div>
      </header>
      
      {/* Progress Bar */}
      <div className="h-1 bg-slate-800">
        <div 
          className="h-full bg-amber-500 transition-all duration-300"
          style={{ width: `${((currentIndex + 1) / artworks.length) * 100}%` }}
        />
      </div>
      
      {/* Main Content */}
      <div className="flex-1 overflow-auto">
        <div className="max-w-lg mx-auto p-4 space-y-4">
          {/* Artwork Image */}
          {currentArtwork && (
            <>
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
                    <p className={`text-amber-400 ${accessible ? 'text-lg' : 'text-sm'}`}>
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
            </>
          )}
          
          {/* Quick Navigation */}
          {accessible && (
            <div className="grid grid-cols-2 gap-3">
              <Button
                onClick={() => handleCommand('previous')}
                disabled={currentIndex === 0}
                className="h-20 text-xl font-semibold rounded-2xl bg-slate-700 hover:bg-slate-600"
              >
                <ChevronLeft className="w-8 h-8 mr-2" />
                Precedente
              </Button>
              <Button
                onClick={() => handleCommand('next')}
                disabled={currentIndex === artworks.length - 1}
                className="h-20 text-xl font-semibold rounded-2xl btn-accent"
              >
                Prossimo
                <ChevronRight className="w-8 h-8 ml-2" />
              </Button>
            </div>
          )}
          
          {/* Command Buttons */}
          <CommandButtons 
            onCommand={handleCommand} 
            accessible={accessible}
            disabledCommands={[]}
          />
        </div>
      </div>
      
      {/* Voice Command Button */}
      <div className="fixed bottom-6 right-6">
        <VoiceCommands onCommand={handleCommand} />
      </div>
      
      {/* Map Modal */}
      {showMap && (
        <MuseumMap
          mapLayout={visit.map_layout}
          artworks={artworks}
          currentArtworkId={currentArtwork?.id}
          onArtworkSelect={(artwork) => {
            const idx = artworks.findIndex(a => a.id === artwork.id);
            if (idx >= 0) {
              setCurrentIndex(idx);
              setShowMap(false);
            }
          }}
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