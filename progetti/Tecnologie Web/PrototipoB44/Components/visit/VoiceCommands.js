import React, { useEffect, useState, useCallback } from 'react';
import { Mic, MicOff } from 'lucide-react';
import { Button } from "@/components/ui/button";
import { toast } from "sonner";

// Controlled vocabulary commands
const COMMANDS = {
  'prossimo': 'next',
  'precedente': 'previous',
  "cos'è questo": 'whatIsThis',
  'dimmi di più': 'more',
  'dimmi di meno': 'less',
  'non capisco': 'simpler',
  'troppo semplice': 'simpler',
  'più semplice': 'simpler',
  "chi è l'autore": 'author',
  "qual è lo stile": 'style',
  "dov'è l'uscita": 'exit',
  "dov'è la toilette": 'toilet',
  "dov'è il bar": 'bar',
  "dov'è lo shop": 'shop',
};

export default function VoiceCommands({ onCommand, disabled = false, disabledCommands = [] }) {
  const [isListening, setIsListening] = useState(false);
  const [recognition, setRecognition] = useState(null);

  useEffect(() => {
    if ('webkitSpeechRecognition' in window || 'SpeechRecognition' in window) {
      const SpeechRecognition = window.SpeechRecognition || window.webkitSpeechRecognition;
      const recog = new SpeechRecognition();
      recog.continuous = false;
      recog.interimResults = false;
      recog.lang = 'it-IT';
      
      recog.onresult = (event) => {
        const transcript = event.results[0][0].transcript.toLowerCase().trim();
        processCommand(transcript);
      };
      
      recog.onerror = (event) => {
        console.error('Speech recognition error:', event.error);
        setIsListening(false);
        if (event.error === 'not-allowed') {
          toast.error('Permesso microfono negato');
        }
      };
      
      recog.onend = () => {
        setIsListening(false);
      };
      
      setRecognition(recog);
    }
    
    return () => {
      if (recognition) {
        recognition.stop();
      }
    };
  }, []);

  const processCommand = useCallback((transcript) => {
    let matched = false;
    for (const [phrase, action] of Object.entries(COMMANDS)) {
      if (transcript.includes(phrase) && !disabledCommands.includes(action)) {
        onCommand(action, transcript);
        matched = true;
        break;
      }
    }
    if (!matched) {
      toast.info(`Comando non riconosciuto: "${transcript}"`);
    }
  }, [onCommand, disabledCommands]);

  const toggleListening = () => {
    if (!recognition) {
      toast.error('Riconoscimento vocale non supportato');
      return;
    }
    
    if (isListening) {
      recognition.stop();
    } else {
      recognition.start();
      setIsListening(true);
    }
  };

  if (disabled) return null;

  return (
    <Button
      onClick={toggleListening}
      variant="outline"
      size="icon"
      className={`rounded-full w-14 h-14 border-2 transition-all ${
        isListening 
          ? 'bg-red-500 border-red-500 text-white animate-pulse' 
          : 'border-amber-500 text-amber-500 hover:bg-amber-500/10'
      }`}
    >
      {isListening ? <Mic className="w-6 h-6" /> : <MicOff className="w-6 h-6" />}
    </Button>
  );
}