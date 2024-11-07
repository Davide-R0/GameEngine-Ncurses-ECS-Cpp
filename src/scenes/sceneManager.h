#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H 

//Da una qualsiasi scena posso creare altre scene o distruggerle o sostituirle con altre e posso anche cambiare scena in base al tag
//serve uno scene manager che controlla, crea, distrugge, sostituisce le scene create da scene
//così si avrebbe come membro un singleton (in entrambi le classi scene e gameEngine) che può essere chiamato sia da scene che gameEngine.
//qui questo assomiglierebbe a qualcosa come: m_sceneManager->getCurrentScene() e (m_sceneManager->update() ???) ... senza dover organizzare la creazione, cambio o altro delle scene. Anzi gameEngine non avrebbe neanche più scene* m_scenes al suo interno, ma solo il sceneManager e si occuperebbe solo di chiamare m_sceneManager->getCurrentScene() quano gli serve.
//

//Nella classe scene, si avrebbe la stessa istanza di sceneManager e si utilizerebbe come:
//  - m_sceneManager->createNewScene(scene* newScene) //crea una nuova scena e la sostituisce nell'array di scene, indipendentemente se ne esiste già una
//  - m_sceneManager->changeSceneFlag(TAG)  //gli dice di flaggare una scena per poter essere attivata (nel prossimo update di sceneManager??? o subito??), controlla che la scena esista già, se non esiste return false e non fa niente
//      
//      Queste due funzioni servono nel caso si vogliano modificare prorpietà di altre scene all'interno della scena attuale
//  - m_sceneManager->getScenes() //retrurn l'array di scene 
//  - m_sceneManager->getScene(TAG) //return la scena con TAG
//  
//  - m_sceneManager->sceneExist(TAG)   //return true se la scena con TAG esiste già, altrimenti false
//

class sceneManager {

};

#endif 
