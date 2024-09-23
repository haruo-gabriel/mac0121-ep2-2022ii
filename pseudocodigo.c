/* Pseudocodigo

se a célula da matriz == (linhas, colunas)
	return 1

se a célula da matriz admite palavra na HORIZONTAL:
	conta o espaço HORIZONTAL disponível
	se existe palavra que encaixe na HORIZONTAL:
		altera os estados da palavra
		empilha essa palavra
		insere essa palavra na matriz HORIZONTAL

		se a célula da matriz admite palavra na VERTICAL:
			conta o espaço VERTICAL disponível
			se existe palavra que encaixe na VERTICAL:
				altera os estados da palavra
				empilha essa palavra
				insere essa palavra na matriz VERTICAL
				pula pra próxima célula
		senão:
			se a pilha estiver vazia:
				return 0
			senão:
				desempilha palavra
				deleta palavra da matriz VERTICAL
				muda os índices pro início dessa palavra
				a partir dessa palavra,
				se existe outra palavra que encaixe na HORIZONTAL:
					altera os estados da palavra
					empilha essa palavra
					insere essa palavra na matriz HORIZONTAL
					
					se a célula da matriz admite palavra na VERTICAL:
						-----


	senão:
		se a pilha estiver vazia:
			return 0
		senão:
			desempilha palavra
			deleta palavra da matriz HORIZONTAL
			muda os índices pro início dessa palavra
			a partir dessa palavra,
			se existe outra palavra que encaixe na HORIZONTAL:
				altera os estados da palavra
				empilha essa palavra
				insere essa palavra na matriz HORIZONTAL
				
				se a célula da matriz admite palavra na VERTICAL:
					-----
				
			senão:
				se a pilha estiver vazia:
					return 0
				senão:
					desempilha palavra
					deleta palavra da matriz HORIZONTAL
					muda os índices pro início da palavra


					a partir dessa palavra,
					se existe outra palavra que encaixe na HORIZONTAL:
						-----

				
senão:
	se a célula da matriz admite palavra na VERTICAL:
		conta o espaço VERTICAL disponível
		se existe palavra que encaixe na VERTICAL:
			empilha essa palavra
			insere essa palavra na matriz HORIZONTAL
			altera os estados da palavra

			pula pra célula seguinte
			se a célula da matriz admite palavra na HORIZONTAL:
				-----
		
		senão:
			
	senão:
		se a pilha estiver vazia:
			return 0
		senão:
			desempilha palavra
			deleta palavra da matriz HORIZONTAL
			muda os índices pro início dessa palavra
			a partir dessa palavra,
			se existe outra palavra que encaixe na HORIZONTAL:
				altera os estados da palavra
				empilha essa palavra
				insere essa palavra na matriz HORIZONTAL
				
				se a célula da matriz admite palavra na VERTICAL:
					-----
				
			senão:
				se a pilha estiver vazia:
					return 0
				senão:
					desempilha palavra
					deleta palavra da matriz HORIZONTAL
					muda os índices pro início da palavra


					a partir dessa palavra,
					se existe outra palavra que encaixe na HORIZONTAL:
						-----


*/
