(define-syntax wtf
  (syntax-rules ()
    [(wtf ...) #t]))

(display (wtf))
(display (wtf 1))
(display (wtf '()))
(display (wtf (1 2 . 3)))
