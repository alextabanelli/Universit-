import React, { useState, useEffect, useRef, useCallback } from 'react';
import { Play, Pause, Square, Volume2, VolumeX } from 'lucide-react';
import { Button } from "@/components/ui/button";
import { Slider } from "@/components/ui/slider";

export default function AudioPlayer({ text, autoPlay = false, accessible = false }) {
  const [isPlaying, setIsPlaying] = useState(false);
  const [isPaused, setIsPaused] = useState(false);
  const [rate, setRate] = useState(1);
  const [progress, setProgress] = useState(0);
  const utteranceRef = useRef(null);
  const intervalRef = useRef(null);

  const speak = useCallback(() => {
    if (!text) return;
    
    window.speechSynthesis.cancel();
    
    const utterance = new SpeechSynthesisUtterance(text);
    utterance.lang = 'it-IT';
    utterance.rate = rate;
    utteranceRef.current = utterance;
    
    utterance.onstart = () => {
      setIsPlaying(true);
      setIsPaused(false);
      // Approximate progress
      const totalTime = (text.length / 10) * (1 / rate) * 1000;
      let elapsed = 0;
      intervalRef.current = setInterval(() => {
        elapsed += 100;
        setProgress(Math.min((elapsed / totalTime) * 100, 100));
      }, 100);
    };
    
    utterance.onend = () => {
      setIsPlaying(false);
      setIsPaused(false);
      setProgress(0);
      clearInterval(intervalRef.current);
    };
    
    utterance.onerror = () => {
      setIsPlaying(false);
      setIsPaused(false);
      setProgress(0);
      clearInterval(intervalRef.current);
    };
    
    window.speechSynthesis.speak(utterance);
  }, [text, rate]);

  useEffect(() => {
    if (autoPlay && text) {
      speak();
    }
    return () => {
      window.speechSynthesis.cancel();
      clearInterval(intervalRef.current);
    };
  }, [text]);

  const togglePlay = () => {
    if (isPlaying && !isPaused) {
      window.speechSynthesis.pause();
      setIsPaused(true);
    } else if (isPaused) {
      window.speechSynthesis.resume();
      setIsPaused(false);
    } else {
      speak();
    }
  };

  const stop = () => {
    window.speechSynthesis.cancel();
    setIsPlaying(false);
    setIsPaused(false);
    setProgress(0);
    clearInterval(intervalRef.current);
  };

  const btnClass = accessible 
    ? 'w-20 h-20 rounded-2xl text-2xl' 
    : 'w-12 h-12 rounded-xl';

  return (
    <div className="glass rounded-2xl p-4">
      {/* Progress bar */}
      <div className="h-1 bg-slate-700 rounded-full mb-4 overflow-hidden">
        <div 
          className="h-full bg-amber-500 transition-all duration-100"
          style={{ width: `${progress}%` }}
        />
      </div>
      
      <div className="flex items-center justify-between gap-4">
        <div className="flex items-center gap-2">
          <Button
            onClick={togglePlay}
            className={`btn-accent ${btnClass}`}
          >
            {isPlaying && !isPaused ? (
              <Pause className={accessible ? 'w-10 h-10' : 'w-6 h-6'} />
            ) : (
              <Play className={accessible ? 'w-10 h-10' : 'w-6 h-6'} />
            )}
          </Button>
          
          <Button
            onClick={stop}
            variant="outline"
            className={`border-slate-600 ${btnClass}`}
            disabled={!isPlaying && !isPaused}
          >
            <Square className={accessible ? 'w-8 h-8' : 'w-5 h-5'} />
          </Button>
        </div>
        
        {!accessible && (
          <div className="flex items-center gap-3 flex-1 max-w-[200px]">
            <Volume2 className="w-4 h-4 text-slate-400" />
            <Slider
              value={[rate]}
              onValueChange={([v]) => setRate(v)}
              min={0.5}
              max={2}
              step={0.25}
              className="flex-1"
            />
            <span className="text-xs text-slate-400 w-8">{rate}x</span>
          </div>
        )}
      </div>
      
      {accessible && (
        <div className="mt-4 flex items-center justify-center gap-4">
          <Button 
            variant="outline" 
            className="border-slate-600 h-14 px-6"
            onClick={() => setRate(Math.max(0.5, rate - 0.25))}
          >
            Più Lento
          </Button>
          <span className="text-lg font-medium w-16 text-center">{rate}x</span>
          <Button 
            variant="outline" 
            className="border-slate-600 h-14 px-6"
            onClick={() => setRate(Math.min(2, rate + 0.25))}
          >
            Più Veloce
          </Button>
        </div>
      )}
    </div>
  );
}