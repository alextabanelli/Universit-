import React from 'react';
import { Button } from "@/components/ui/button";
import { 
  ChevronLeft, 
  ChevronRight, 
  HelpCircle, 
  Plus, 
  Minus, 
  User, 
  Palette,
  DoorOpen,
  Coffee,
  ShoppingBag
} from 'lucide-react';

const COMMAND_BUTTONS = [
  { id: 'previous', label: 'Precedente', icon: ChevronLeft, color: 'bg-slate-700' },
  { id: 'next', label: 'Prossimo', icon: ChevronRight, color: 'bg-slate-700' },
  { id: 'whatIsThis', label: "Cos'è questo?", icon: HelpCircle, color: 'bg-blue-600' },
  { id: 'more', label: 'Dimmi di più', icon: Plus, color: 'bg-emerald-600' },
  { id: 'less', label: 'Dimmi di meno', icon: Minus, color: 'bg-orange-600' },
  { id: 'simpler', label: 'Più semplice', icon: HelpCircle, color: 'bg-purple-600' },
  { id: 'author', label: "Chi è l'autore?", icon: User, color: 'bg-cyan-600' },
  { id: 'style', label: 'Qual è lo stile?', icon: Palette, color: 'bg-pink-600' },
];

const FACILITY_BUTTONS = [
  { id: 'exit', label: 'Uscita', icon: DoorOpen },
  { id: 'toilet', label: 'Toilette', icon: DoorOpen },
  { id: 'bar', label: 'Bar', icon: Coffee },
  { id: 'shop', label: 'Shop', icon: ShoppingBag },
];

export default function CommandButtons({ 
  onCommand, 
  accessible = false, 
  disabledCommands = [],
  showFacilities = true 
}) {
  const baseClass = accessible 
    ? 'h-20 text-lg font-semibold rounded-2xl' 
    : 'h-12 text-sm rounded-xl';

  return (
    <div className="space-y-4">
      {/* Main Commands */}
      <div className={`grid ${accessible ? 'grid-cols-2 gap-3' : 'grid-cols-4 gap-2'}`}>
        {COMMAND_BUTTONS.map((btn) => {
          const isDisabled = disabledCommands.includes(btn.id);
          return (
            <Button
              key={btn.id}
              onClick={() => onCommand(btn.id)}
              disabled={isDisabled}
              className={`${btn.color} hover:opacity-90 ${baseClass} ${
                isDisabled ? 'opacity-40 cursor-not-allowed' : ''
              } flex flex-col items-center justify-center gap-1`}
            >
              <btn.icon className={accessible ? 'w-7 h-7' : 'w-4 h-4'} />
              <span className={accessible ? '' : 'text-xs'}>{btn.label}</span>
            </Button>
          );
        })}
      </div>
      
      {/* Facility Buttons */}
      {showFacilities && (
        <div className="pt-2 border-t border-slate-800">
          <p className="text-xs text-slate-500 mb-2 uppercase tracking-wider">Dove si trova...</p>
          <div className="flex gap-2 flex-wrap">
            {FACILITY_BUTTONS.map((btn) => (
              <Button
                key={btn.id}
                onClick={() => onCommand(btn.id)}
                variant="outline"
                className={`border-slate-700 hover:bg-slate-800 ${accessible ? 'h-14 px-6' : 'h-10 px-4'}`}
              >
                <btn.icon className="w-4 h-4 mr-2" />
                {btn.label}
              </Button>
            ))}
          </div>
        </div>
      )}
    </div>
  );
}