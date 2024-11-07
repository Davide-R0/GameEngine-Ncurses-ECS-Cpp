# masterManager
Utilizzo: Organizza, inizializza e chiude tutti i manager nell'applicazione
Conftiene la lista di tutti i manager del sistema ed è in grado di eeguire operazioni in parallelo (uguali) per tutti i manager. E' in grado di aggiungere (inizializzare) e togliere manager, flaggarli per certe attivita, ecc...

- Tipo: Oggetto singleton
- Interazioni:
    - GameEngine:
        - tipo: oggetto singleton
        - tipo di relazione: composizione
    - sceneManager
        - tipo: oggetto singleton
        - tipo di relazione: composizione 
    - sceneManager
        - tipo: oggetto singleton
        - tipo di relazione: composizione 
- Specifiche Interazioni:
    - GameEngine:
        - update()
            - fa l'update di tuttii i manager che contiene
        - addManager(manager_tag)
            - aggiunge un manager (lo inizializza)
            - controlla le dipendenze per poterlo inizializzare??? (lasciarlo fare al manager??)
        - removeManager(manager_tag)
            - rimuove il manager (lo distrugge)
        - setManagerFlag(manager_tag)
            - attivare, disattivare specifiche flag per certi manager
        - ...
    - sceneManager:
        - setManagerUpdateFunction()
            - imposta la funzione da chiamare all'interno della funzione update()
        - ...

