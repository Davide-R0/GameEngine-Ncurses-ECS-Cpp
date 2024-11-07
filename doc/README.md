> Da aggiornare ancora

La creazione di oggetti avviene tramite prima la def di uno struct che viene poi passato alla funzione che crea l'oggetto (e ne restituisce l'id?)


## Nota sullo studio dell'architrttura del engine

In generale ogni pezzo di xodice deve essere `decoupled` dagli altri.

Nella creazione e progettazione (prima della effettiva scrittura?) di uno di questi pacchetti (che possono essere una o più classi oppure anche solo un insieme di funzioni...) si devono determinare le seguenti informazioni:
- La parte più importante è come questo pacchetto andrà ad interagire con gli altri già creati o che in futuro si creeranno, quindi detrminare:
    - Con quali altri pacchetti esso interagirà
    - In che maniera interagirà
- Determinare le funzioni concrete che ogni interazione con altri pacchetti necessiterà. Cioè non determinare il funzionamento del pacchetto, ma cosa si vuole essere in grado di fare con il suo utilizzo rispetto ad ogni altro pacchetto con cui interagirà.

#### Esempio:
**SceneManager**
- Tipo: oggetto singolo (c++)
- Interazioni:
    - GameEngine:
        - tipo: oggetto singolo (cioè il tipo di pacchetto che è gameEngine) 
        - tipo di relazione: composizione (la relazione che questo pacchetto ha con il pacchetto in questione, sceneManager. Composizione in questo caso è nel senso di c++)
    - scene:
        - tipo: oggetto singolo 
        - tipo di relazione: composizione
- Specifiche interazioni: (Come si vuole che ogniuno di essi (gameEngine, scene) interagisca con senenManager. Quindi come ad esempio si vuole che gameEngine utilizzi il sceneManager nel codice)
    - classe gameEngine: (lista delle funzioni che probabilmente saranno chiamate da gameEngine in sceneManager e spiegazione veloce del significato e utilizzo di esse)
        - update() 
            - Spiegazione veloce: per update della scena attuale, per impostare la scena attuale nel caso in cui sia stata attivata una flag di cambio di scena (impostata all'interno di una scena)
        - getCurrentScene()  
            - per ottenere la scena attuale 
        - ...?
    - classe scene:    
        - m_sceneManager->createNewScene(scene* newScene) 
            - crea una nuova scena e la sostituisce (nel caso in cui sia già presente) nell'array di scene, indipendentemente se ne esiste già una
        - m_sceneManager->changeSceneFlag(TAG)  
            - gli dice di flaggare una scena per poter essere attivata (nel prossimo update di sceneManager??? o subito??), controlla che la scena esista già, se non esiste return false e non fa niente
        - m_sceneManager->getScenes() 
            - retrurn l'array di scene 
            - (Queste funzione serve nel caso si voglia modificare prorpietà di altre scene all'interno della scena attuale)
        - m_sceneManager->getScene(TAG) 
            - return la scena con TAG 
            - (Queste funzione serve nel caso si voglia modificare prorpietà di altre scene all'interno della scena attuale)
        - m_sceneManager->sceneExist(TAG)   
            - return true se la scena con TAG esiste già, altrimenti false


Se il pacchetto fosse stato composto da più parti logiche allora si sarebbero composte fino ad ottenere uno schema simile a quello dell'esempio 


