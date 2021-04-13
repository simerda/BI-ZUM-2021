(define (domain mapf)
	(:requirements 
		:strips
		:typing )
	
	(:types 
		agent
		vertex)
   (:predicates
	(edge	?v1  ?v2 - vertex)
	(at		?a       - agent ?v - vertex)
	(empty	?v       - vertex)
   )
	(:action move                                
		:parameters (
		?a - agent    ?from ?to - vertex
		)

		:precondition (
		    and (edge ?from ?to)
				         (at ?a ?from)
				         (empty ?to)
         )

		:effect (
		    and (at ?a ?to) (empty ?from)
                (not (empty ?to)) (not (at ?a ?from))
	    )
  
    )
)