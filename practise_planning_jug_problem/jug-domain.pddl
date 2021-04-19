(define (domain jug)
	(:requirements 
		:strips
		:typing
		:fluents )
	
	(:types 
		jug)
   (:functions
	(capacity	?j - jug)
	(volume		?j - jug)
   )
	(:predicates )
	(:action fill                                
		:parameters (
		?j - jug
		)

		:effect (
		    and (assign (volume ?j) (capacity ?j))
	    )
  
    )
	(:action empty                                
		:parameters (
		?j - jug
		)

		:effect (
		    and (assign (volume ?j) 0)
	    )
  
    )
	(:action pour                                
		:parameters (
		?j1 ?j2 - jug
		)

		:precondition (<= (+ (volume ?j1) (volume ?j2)) (capacity ?j1))

		:effect (
		    and 
	        (assign (volume ?j1) (+ (volume ?j1) (volume ?j2)))
	        (assign (volume ?j2) 0) 
        )
  
    )
	(:action pour_overflow                                
		:parameters (
		?j1 ?j2 - jug
		)

		:precondition (> (+ (volume ?j1) (volume ?j2)) (capacity ?j1))

		:effect (
		    and
            (assign (volume ?j2)  (- (+ (volume ?j1) (volume ?j2) ) (capacity ?j1) ))
            (assign (volume ?j1) (capacity ?j1))
        )
  
    )
)
