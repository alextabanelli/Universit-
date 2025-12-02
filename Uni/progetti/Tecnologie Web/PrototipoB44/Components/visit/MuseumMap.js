import React from 'react';
import { X, MapPin, DoorOpen, Coffee, ShoppingBag } from 'lucide-react';
import { Button } from "@/components/ui/button";

const FACILITY_ICONS = {
  exit: DoorOpen,
  toilet: DoorOpen,
  bar: Coffee,
  shop: ShoppingBag,
};

export default function MuseumMap({ 
  mapLayout, 
  artworks = [], 
  currentArtworkId,
  onArtworkSelect,
  onClose,
  highlightedFacility 
}) {
  if (!mapLayout) {
    return (
      <div className="fixed inset-0 z-50 bg-slate-950/95 flex items-center justify-center p-4">
        <div className="glass rounded-2xl p-6 max-w-sm w-full text-center">
          <p className="text-slate-400">Mappa non disponibile per questa visita</p>
          <Button onClick={onClose} className="mt-4 btn-accent">Chiudi</Button>
        </div>
      </div>
    );
  }

  const { width = 400, height = 300, rooms = [], facilities = [] } = mapLayout;
  const scale = Math.min(350 / width, 500 / height);

  return (
    <div className="fixed inset-0 z-50 bg-slate-950/95 flex flex-col">
      {/* Header */}
      <div className="flex items-center justify-between p-4 border-b border-slate-800">
        <h2 className="text-xl font-semibold">Mappa Museo</h2>
        <Button variant="ghost" size="icon" onClick={onClose}>
          <X className="w-6 h-6" />
        </Button>
      </div>
      
      {/* Map Container */}
      <div className="flex-1 overflow-auto p-4 flex items-center justify-center">
        <svg 
          viewBox={`0 0 ${width} ${height}`}
          className="max-w-full max-h-full"
          style={{ maxWidth: width * scale, maxHeight: height * scale }}
        >
          {/* Rooms */}
          {rooms.map((room) => (
            <g key={room.id}>
              <rect
                x={room.x}
                y={room.y}
                width={room.width}
                height={room.height}
                fill="rgba(51, 65, 85, 0.5)"
                stroke="rgba(148, 163, 184, 0.3)"
                strokeWidth="2"
                rx="4"
              />
              <text
                x={room.x + room.width / 2}
                y={room.y + 16}
                textAnchor="middle"
                fill="#94a3b8"
                fontSize="10"
                fontWeight="500"
              >
                {room.name}
              </text>
            </g>
          ))}
          
          {/* Artworks */}
          {artworks.map((artwork) => {
            const isActive = artwork.id === currentArtworkId;
            return (
              <g 
                key={artwork.id}
                onClick={() => onArtworkSelect?.(artwork)}
                style={{ cursor: onArtworkSelect ? 'pointer' : 'default' }}
              >
                <circle
                  cx={artwork.position_x || 50}
                  cy={artwork.position_y || 50}
                  r={isActive ? 12 : 8}
                  fill={isActive ? '#f59e0b' : '#475569'}
                  stroke={isActive ? '#fbbf24' : '#64748b'}
                  strokeWidth="2"
                  className="transition-all"
                />
                {isActive && (
                  <circle
                    cx={artwork.position_x || 50}
                    cy={artwork.position_y || 50}
                    r="18"
                    fill="none"
                    stroke="#f59e0b"
                    strokeWidth="2"
                    opacity="0.5"
                    className="animate-ping"
                  />
                )}
              </g>
            );
          })}
          
          {/* Facilities */}
          {facilities.map((facility, i) => {
            const isHighlighted = highlightedFacility === facility.type;
            return (
              <g key={i}>
                <rect
                  x={facility.x - 10}
                  y={facility.y - 10}
                  width="20"
                  height="20"
                  fill={isHighlighted ? '#22c55e' : '#1e293b'}
                  stroke={isHighlighted ? '#4ade80' : '#475569'}
                  strokeWidth="2"
                  rx="4"
                  className={isHighlighted ? 'animate-pulse' : ''}
                />
                <text
                  x={facility.x}
                  y={facility.y + 4}
                  textAnchor="middle"
                  fill={isHighlighted ? '#fff' : '#94a3b8'}
                  fontSize="10"
                >
                  {facility.type === 'exit' && '🚪'}
                  {facility.type === 'toilet' && '🚻'}
                  {facility.type === 'bar' && '☕'}
                  {facility.type === 'shop' && '🛍️'}
                </text>
              </g>
            );
          })}
        </svg>
      </div>
      
      {/* Legend */}
      <div className="p-4 border-t border-slate-800">
        <div className="flex flex-wrap gap-4 justify-center text-xs text-slate-400">
          <div className="flex items-center gap-2">
            <div className="w-4 h-4 rounded-full bg-amber-500" />
            <span>Opera corrente</span>
          </div>
          <div className="flex items-center gap-2">
            <div className="w-3 h-3 rounded-full bg-slate-600 border border-slate-500" />
            <span>Altre opere</span>
          </div>
        </div>
      </div>
    </div>
  );
}