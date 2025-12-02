import React, { useState, useEffect } from 'react';
import { Link, useLocation } from 'react-router-dom';
import { createPageUrl } from '../../utils';
import { base44 } from '@/api/base44Client';
import { 
  LayoutDashboard, 
  Building2, 
  Image, 
  Route, 
  Users, 
  ShoppingCart,
  Settings,
  Menu,
  X,
  LogOut,
  ChevronDown
} from 'lucide-react';
import { Button } from "@/components/ui/button";
import {
  DropdownMenu,
  DropdownMenuContent,
  DropdownMenuItem,
  DropdownMenuTrigger,
} from "@/components/ui/dropdown-menu";

const navItems = [
  { label: 'Dashboard', icon: LayoutDashboard, page: 'EditorDashboard' },
  { label: 'Musei', icon: Building2, page: 'MuseumManager' },
  { label: 'Contenuti', icon: Image, page: 'ContentBrowser' },
  { label: 'Visite', icon: Route, page: 'VisitManager' },
  { label: 'Sessioni', icon: Users, page: 'DocentePanel' },
  { label: 'Marketplace', icon: ShoppingCart, page: 'MarketplaceManager' },
];

export default function EditorLayout({ children, currentPage }) {
  const [user, setUser] = useState(null);
  const [sidebarOpen, setSidebarOpen] = useState(false);

  useEffect(() => {
    base44.auth.me().then(setUser).catch(() => {});
  }, []);

  const handleLogout = () => {
    base44.auth.logout();
  };

  return (
    <div className="min-h-screen bg-slate-100 flex">
      {/* Sidebar - Desktop */}
      <aside className="hidden lg:flex lg:flex-col lg:w-64 bg-slate-900 text-white">
        <div className="p-4 border-b border-slate-700">
          <Link to={createPageUrl('EditorDashboard')} className="flex items-center gap-3">
            <div className="w-10 h-10 rounded-xl bg-gradient-to-br from-amber-500 to-orange-600 flex items-center justify-center">
              <Image className="w-6 h-6 text-white" />
            </div>
            <div>
              <h1 className="font-bold">ArtAround</h1>
              <p className="text-xs text-slate-400">Editor & Marketplace</p>
            </div>
          </Link>
        </div>
        
        <nav className="flex-1 p-4 space-y-1">
          {navItems.map((item) => {
            const isActive = currentPage === item.page;
            return (
              <Link
                key={item.page}
                to={createPageUrl(item.page)}
                className={`flex items-center gap-3 px-4 py-3 rounded-lg transition-colors ${
                  isActive 
                    ? 'bg-amber-500 text-white' 
                    : 'text-slate-300 hover:bg-slate-800'
                }`}
              >
                <item.icon className="w-5 h-5" />
                <span>{item.label}</span>
              </Link>
            );
          })}
        </nav>
        
        <div className="p-4 border-t border-slate-700">
          <Link to={createPageUrl('Home')}>
            <Button variant="outline" className="w-full border-slate-600 text-slate-300 hover:bg-slate-800">
              Apri Navigator
            </Button>
          </Link>
        </div>
      </aside>

      {/* Mobile Header */}
      <div className="lg:hidden fixed top-0 left-0 right-0 bg-slate-900 text-white z-50">
        <div className="flex items-center justify-between p-4">
          <button onClick={() => setSidebarOpen(true)}>
            <Menu className="w-6 h-6" />
          </button>
          <h1 className="font-bold">ArtAround Editor</h1>
          <div className="w-6" />
        </div>
      </div>

      {/* Mobile Sidebar */}
      {sidebarOpen && (
        <div className="lg:hidden fixed inset-0 z-50">
          <div className="absolute inset-0 bg-black/50" onClick={() => setSidebarOpen(false)} />
          <aside className="absolute left-0 top-0 bottom-0 w-64 bg-slate-900 text-white">
            <div className="p-4 border-b border-slate-700 flex items-center justify-between">
              <span className="font-bold">Menu</span>
              <button onClick={() => setSidebarOpen(false)}>
                <X className="w-6 h-6" />
              </button>
            </div>
            <nav className="p-4 space-y-1">
              {navItems.map((item) => {
                const isActive = currentPage === item.page;
                return (
                  <Link
                    key={item.page}
                    to={createPageUrl(item.page)}
                    onClick={() => setSidebarOpen(false)}
                    className={`flex items-center gap-3 px-4 py-3 rounded-lg transition-colors ${
                      isActive 
                        ? 'bg-amber-500 text-white' 
                        : 'text-slate-300 hover:bg-slate-800'
                    }`}
                  >
                    <item.icon className="w-5 h-5" />
                    <span>{item.label}</span>
                  </Link>
                );
              })}
            </nav>
          </aside>
        </div>
      )}

      {/* Main Content */}
      <main className="flex-1 lg:ml-0">
        {/* Top Bar */}
        <header className="bg-white border-b border-slate-200 px-6 py-4 lg:block hidden">
          <div className="flex items-center justify-end">
            {user && (
              <DropdownMenu>
                <DropdownMenuTrigger asChild>
                  <button className="flex items-center gap-2 text-sm text-slate-600 hover:text-slate-900">
                    <div className="w-8 h-8 rounded-full bg-slate-200 flex items-center justify-center">
                      {user.full_name?.[0] || user.email[0].toUpperCase()}
                    </div>
                    <span>{user.full_name || user.email}</span>
                    <ChevronDown className="w-4 h-4" />
                  </button>
                </DropdownMenuTrigger>
                <DropdownMenuContent align="end">
                  <DropdownMenuItem onClick={handleLogout}>
                    <LogOut className="w-4 h-4 mr-2" />
                    Logout
                  </DropdownMenuItem>
                </DropdownMenuContent>
              </DropdownMenu>
            )}
          </div>
        </header>

        <div className="p-6 lg:pt-6 pt-20">
          {children}
        </div>
      </main>
    </div>
  );
}