import React from 'react';
import { Link } from 'react-router-dom';
import { createPageUrl } from './utils';
import { Home, Map, Users, Menu, X } from 'lucide-react';
import { useState } from 'react';

export default function Layout({ children, currentPageName }) {
  const [menuOpen, setMenuOpen] = useState(false);
  
  const navItems = [
    { name: 'Home', page: 'Home', icon: Home },
    { name: 'Visite', page: 'Marketplace', icon: Map },
    { name: 'Sessione', page: 'JoinSession', icon: Users },
  ];

  const hideNav = ['VisitPlayer', 'SyncVisit', 'Quiz'].includes(currentPageName);

  return (
    <div className="min-h-screen bg-slate-950 text-white">
      <style>{`
        :root {
          --accent: #f59e0b;
          --accent-light: #fbbf24;
        }
        .btn-accent {
          background: linear-gradient(135deg, #f59e0b, #d97706);
        }
        .btn-accent:hover {
          background: linear-gradient(135deg, #fbbf24, #f59e0b);
        }
        .glass {
          background: rgba(15, 23, 42, 0.8);
          backdrop-filter: blur(12px);
          border: 1px solid rgba(255,255,255,0.1);
        }
        @keyframes fadeIn {
          from { opacity: 0; transform: translateY(10px); }
          to { opacity: 1; transform: translateY(0); }
        }
        .animate-fadeIn {
          animation: fadeIn 0.3s ease-out;
        }
      `}</style>
      
      {!hideNav && (
        <header className="fixed top-0 left-0 right-0 z-50 glass">
          <div className="max-w-lg mx-auto px-4 py-3 flex items-center justify-between">
            <Link to={createPageUrl('Home')} className="flex items-center gap-2">
              <div className="w-8 h-8 rounded-lg btn-accent flex items-center justify-center">
                <Map className="w-5 h-5 text-slate-900" />
              </div>
              <span className="font-semibold text-lg">ArtAround</span>
            </Link>
            
            <button 
              onClick={() => setMenuOpen(!menuOpen)}
              className="p-2 rounded-lg hover:bg-slate-800 transition-colors"
            >
              {menuOpen ? <X className="w-6 h-6" /> : <Menu className="w-6 h-6" />}
            </button>
          </div>
          
          {menuOpen && (
            <nav className="absolute top-full left-0 right-0 glass animate-fadeIn">
              <div className="max-w-lg mx-auto px-4 py-2">
                {navItems.map((item) => (
                  <Link
                    key={item.page}
                    to={createPageUrl(item.page)}
                    onClick={() => setMenuOpen(false)}
                    className={`flex items-center gap-3 px-4 py-3 rounded-lg transition-colors ${
                      currentPageName === item.page 
                        ? 'bg-amber-500/20 text-amber-400' 
                        : 'hover:bg-slate-800'
                    }`}
                  >
                    <item.icon className="w-5 h-5" />
                    <span>{item.name}</span>
                  </Link>
                ))}
              </div>
            </nav>
          )}
        </header>
      )}
      
      <main className={!hideNav ? 'pt-16' : ''}>
        {children}
      </main>
      
      {!hideNav && (
        <nav className="fixed bottom-0 left-0 right-0 glass border-t border-slate-800">
          <div className="max-w-lg mx-auto px-4 py-2 flex justify-around">
            {navItems.map((item) => (
              <Link
                key={item.page}
                to={createPageUrl(item.page)}
                className={`flex flex-col items-center gap-1 p-2 rounded-lg transition-colors ${
                  currentPageName === item.page 
                    ? 'text-amber-400' 
                    : 'text-slate-400 hover:text-white'
                }`}
              >
                <item.icon className="w-6 h-6" />
                <span className="text-xs">{item.name}</span>
              </Link>
            ))}
          </div>
        </nav>
      )}
    </div>
  );
}