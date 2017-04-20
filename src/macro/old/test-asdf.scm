(define proc2
  (lambda ()
    (define-syntax define
      (syntax-rules ()
        [(_ a b)
         (display "foo you")]))
    (define 1 2)    
))

(proc2)
