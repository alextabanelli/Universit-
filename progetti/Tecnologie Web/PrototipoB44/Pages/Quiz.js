import React, { useState, useEffect } from 'react';
import { useNavigate } from 'react-router-dom';
import { createPageUrl } from '../utils';
import { base44 } from '@/api/base44Client';
import { useQuery } from '@tanstack/react-query';
import { 
  CheckCircle2, 
  XCircle, 
  Loader2, 
  Award,
  ChevronRight,
  RotateCcw,
  Home
} from 'lucide-react';
import { Button } from "@/components/ui/button";
import { toast } from "sonner";
import { Progress } from "@/components/ui/progress";

export default function Quiz() {
  const navigate = useNavigate();
  const urlParams = new URLSearchParams(window.location.search);
  const sessionId = urlParams.get('sessionId');
  
  const [currentQuestion, setCurrentQuestion] = useState(0);
  const [answers, setAnswers] = useState([]);
  const [selectedAnswer, setSelectedAnswer] = useState(null);
  const [showResult, setShowResult] = useState(false);
  const [quizResult, setQuizResult] = useState(null);
  const [submitting, setSubmitting] = useState(false);

  const { data: session } = useQuery({
    queryKey: ['session', sessionId],
    queryFn: async () => {
      const sessions = await base44.entities.Session.filter({ id: sessionId });
      return sessions[0];
    },
    enabled: !!sessionId,
  });

  const { data: quiz, isLoading: quizLoading } = useQuery({
    queryKey: ['quiz', session?.visit_id],
    queryFn: async () => {
      const quizzes = await base44.entities.Quiz.filter({ 
        visit_id: session.visit_id,
        is_active: true 
      });
      return quizzes[0];
    },
    enabled: !!session?.visit_id,
  });

  const questions = quiz?.questions || [];
  const question = questions[currentQuestion];
  const progress = ((currentQuestion + 1) / Math.max(questions.length, 1)) * 100;

  const handleAnswerSelect = (index) => {
    if (showResult) return;
    setSelectedAnswer(index);
  };

  const handleNext = async () => {
    if (selectedAnswer === null) {
      toast.error('Seleziona una risposta');
      return;
    }

    const newAnswers = [...answers, {
      question_id: question.id,
      selected_index: selectedAnswer
    }];
    setAnswers(newAnswers);

    if (currentQuestion < questions.length - 1) {
      setCurrentQuestion(prev => prev + 1);
      setSelectedAnswer(null);
    } else {
      // Submit quiz
      await submitQuiz(newAnswers);
    }
  };

  const submitQuiz = async (finalAnswers) => {
    setSubmitting(true);
    
    try {
      // Calculate score
      let score = 0;
      finalAnswers.forEach((answer) => {
        const q = questions.find(q => q.id === answer.question_id);
        if (q && q.correct_index === answer.selected_index) {
          score++;
        }
      });

      const percentage = Math.round((score / questions.length) * 100);

      // Get current user
      let userEmail = 'anonymous';
      try {
        const user = await base44.auth.me();
        userEmail = user.email;
      } catch (e) {
        // User not logged in
      }

      // Save result
      const result = await base44.entities.QuizResult.create({
        session_id: sessionId,
        quiz_id: quiz.id,
        user_email: userEmail,
        answers: finalAnswers,
        score: score,
        total_questions: questions.length,
        percentage: percentage,
        completed_at: new Date().toISOString()
      });

      setQuizResult({
        score,
        total: questions.length,
        percentage
      });
      setShowResult(true);
    } catch (error) {
      console.error('Error submitting quiz:', error);
      toast.error('Errore nel salvataggio del quiz');
    } finally {
      setSubmitting(false);
    }
  };

  if (quizLoading) {
    return (
      <div className="min-h-screen flex items-center justify-center bg-slate-950">
        <Loader2 className="w-10 h-10 text-violet-500 animate-spin" />
      </div>
    );
  }

  if (!quiz || questions.length === 0) {
    return (
      <div className="min-h-screen flex flex-col items-center justify-center p-6 bg-slate-950">
        <div className="glass rounded-2xl p-8 text-center max-w-sm">
          <Award className="w-16 h-16 text-violet-500 mx-auto mb-4" />
          <h2 className="text-xl font-bold mb-2">Visita Completata!</h2>
          <p className="text-slate-400 mb-6">
            Non è disponibile un quiz per questa visita.
          </p>
          <Button 
            onClick={() => navigate(createPageUrl('Home'))}
            className="btn-accent"
          >
            <Home className="w-5 h-5 mr-2" />
            Torna alla Home
          </Button>
        </div>
      </div>
    );
  }

  // Results Screen
  if (showResult && quizResult) {
    const isPassed = quizResult.percentage >= 60;
    
    return (
      <div className="min-h-screen flex flex-col items-center justify-center p-6 bg-slate-950">
        <div className="glass rounded-2xl p-8 text-center max-w-sm w-full">
          <div className={`w-24 h-24 rounded-full mx-auto mb-6 flex items-center justify-center ${
            isPassed ? 'bg-green-500/20' : 'bg-orange-500/20'
          }`}>
            {isPassed ? (
              <Award className="w-12 h-12 text-green-500" />
            ) : (
              <RotateCcw className="w-12 h-12 text-orange-500" />
            )}
          </div>
          
          <h2 className="text-2xl font-bold mb-2">
            {isPassed ? 'Complimenti!' : 'Continua a studiare!'}
          </h2>
          
          <p className="text-slate-400 mb-6">
            {isPassed 
              ? 'Hai superato il quiz con successo.' 
              : 'Non hai raggiunto il punteggio minimo.'}
          </p>
          
          <div className="bg-slate-800 rounded-2xl p-6 mb-6">
            <div className="text-5xl font-bold mb-2" style={{
              color: isPassed ? '#22c55e' : '#f97316'
            }}>
              {quizResult.percentage}%
            </div>
            <p className="text-slate-400">
              {quizResult.score} / {quizResult.total} risposte corrette
            </p>
          </div>
          
          <div className="space-y-3">
            <Button 
              onClick={() => navigate(createPageUrl('Home'))}
              className="w-full h-14 text-lg btn-accent rounded-xl"
            >
              <Home className="w-5 h-5 mr-2" />
              Torna alla Home
            </Button>
          </div>
        </div>
      </div>
    );
  }

  return (
    <div className="min-h-screen bg-slate-950 flex flex-col">
      {/* Header */}
      <header className="glass border-b border-slate-800 p-4">
        <div className="max-w-lg mx-auto">
          <div className="flex items-center justify-between mb-3">
            <h1 className="font-semibold">Quiz Finale</h1>
            <span className="text-sm text-slate-400">
              {currentQuestion + 1} / {questions.length}
            </span>
          </div>
          <Progress value={progress} className="h-2 bg-slate-800" />
        </div>
      </header>
      
      {/* Question */}
      <div className="flex-1 p-4">
        <div className="max-w-lg mx-auto space-y-6">
          <div className="glass rounded-2xl p-6">
            <p className="text-lg font-medium leading-relaxed">
              {question?.question}
            </p>
          </div>
          
          {/* Options */}
          <div className="space-y-3">
            {question?.options?.map((option, index) => (
              <button
                key={index}
                onClick={() => handleAnswerSelect(index)}
                className={`w-full p-4 rounded-xl text-left transition-all ${
                  selectedAnswer === index
                    ? 'bg-violet-600 border-2 border-violet-400'
                    : 'glass border-2 border-transparent hover:border-slate-600'
                }`}
              >
                <div className="flex items-center gap-3">
                  <div className={`w-8 h-8 rounded-full flex items-center justify-center flex-shrink-0 ${
                    selectedAnswer === index 
                      ? 'bg-white text-violet-600' 
                      : 'bg-slate-700 text-slate-400'
                  }`}>
                    {String.fromCharCode(65 + index)}
                  </div>
                  <span className={selectedAnswer === index ? 'text-white' : 'text-slate-300'}>
                    {option}
                  </span>
                </div>
              </button>
            ))}
          </div>
        </div>
      </div>
      
      {/* Footer */}
      <div className="glass border-t border-slate-800 p-4">
        <div className="max-w-lg mx-auto">
          <Button
            onClick={handleNext}
            disabled={selectedAnswer === null || submitting}
            className="w-full h-14 text-lg bg-violet-600 hover:bg-violet-700 rounded-xl"
          >
            {submitting ? (
              <Loader2 className="w-5 h-5 animate-spin" />
            ) : currentQuestion < questions.length - 1 ? (
              <>
                Prossima Domanda
                <ChevronRight className="w-5 h-5 ml-2" />
              </>
            ) : (
              <>
                Termina Quiz
                <CheckCircle2 className="w-5 h-5 ml-2" />
              </>
            )}
          </Button>
        </div>
      </div>
    </div>
  );
}