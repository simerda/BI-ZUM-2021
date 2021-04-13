(define (domain assembler)
	(:requirements 
		:strips
		:typing
		)
	
	(:types 
		register
		index
		memory
		data
		)
   (:predicates
	(stores	    ?m - memory ?i - index ?d - data)
	(caches		?r - register ?d - data)
	(empty ?m - memory ?i - index)
   )
	(:action load                                
		:parameters (
		?m - memory    ?r - register ?i - index ?d ?garbage - data
		)

		:precondition (
		    and (stores ?m ?i ?d) (not (empty ?m ?i)) (caches ?r ?garbage )
         )

		:effect (
		    and (caches ?r ?d) (not (caches ?r ?garbage))
	    )
  
    )
	(:action empty                                
		:parameters (
		?m - memory  ?i - index ?d - data
		)

		:precondition (
		    and (stores ?m ?i ?d)
         )

		:effect (
		    and (not (stores ?m ?i ?d)) (empty ?m ?i)
	    )
  
    )
	(:action store                                
		:parameters (
		?m - memory  ?r - register ?i - index ?d - data
		)

		:precondition (
		    and (caches ?r ?d) (empty ?m ?i)
         )

		:effect (
		    and (stores ?m ?i ?d) (not (empty ?m ?i))
	    )
  
    )
)