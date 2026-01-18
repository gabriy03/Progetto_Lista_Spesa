#include <iostream>
#include <list>
#include <string>
#include <cstdio>
#include "Utente.h"
#include "ListaSpesa.h"
#include "Grafica.h"
#include "Prodotto.h"

void pausa() {
    std::cout << "\nPremi INVIO per continuare...";
    if (std::cin.peek() == '\n')
        std::cin.ignore();
    std::cin.get();
}

int main() {
    // Creo la lista che conterrà tutti gli utenti caricati in memoria
    std::list<Utente*> databaseUtenti;

    // Carico gli utenti e se il file non esiste la lista resta vuota
    Utente::caricaUtenti("utenti.txt", databaseUtenti);

    Utente* utenteLoggato = nullptr;


    while (true) {

        // =========================================================
        // MENU INIZIALE (Login / Registrazione)
        // =========================================================
        if (utenteLoggato == nullptr) {
            Grafica::pulisciSchermo();
            std::cout << "=== APP LISTA SPESA ===" << std::endl;
            std::cout << "1. Login" << std::endl;
            std::cout << "2. Registrazione Nuovo Utente" << std::endl;
            std::cout << "0. Esci" << std::endl;
            std::cout << "=======================" << std::endl;
            std::cout << "> Scelta: ";

            int scelta;
            std::cin >> scelta;

            // Esce e chiude il programma
            if (scelta == 0) {
                break;
            }

            // --- LOGIN ---
            if (scelta == 1) {
                std::string nick, pass;
                std::cout << "Nickname: "; std::cin >> nick;
                std::cout << "Password: "; std::cin >> pass;

                bool trovato = false;
                for (auto* u : databaseUtenti) {
                    if (u->login(nick, pass)) {
                        utenteLoggato = u;
                        trovato = true;
                        break;
                    }
                }

                if (!trovato) {
                    std::cout << "Errore: Credenziali non valide.\n";
                    pausa();
                }
            }
            // --- REGISTRAZIONE ---
            else if (scelta == 2) {
                std::string nick, pass;
                std::cout << "Scegli Nickname: "; std::cin >> nick;
                std::cout << "Scegli Password: "; std::cin >> pass;

                // Controllo se il nickname esiste già
                bool esiste = false;
                for(auto* u : databaseUtenti) {
                    if(u->getNickname() == nick)
                        esiste = true;
                }

                if(!esiste) {
                    Utente* nuovo = new Utente(nick, pass);
                    databaseUtenti.push_back(nuovo);
                    Utente::salvaUtenti("utenti.txt", databaseUtenti);
                    std::cout << "Registrazione completata! Ora effettua il login.\n";
                } else {
                    std::cout << "Errore: Nickname gia' in uso.\n";
                }
                pausa();
            }
        }

        // =========================================================
        // MENU' UTENTE (Selezione Liste)
        // =========================================================
        else {
            Grafica::pulisciSchermo();
            std::cout << "Utente connesso: " << utenteLoggato->getNickname() << std::endl;
            std::cout << "--- LE TUE LISTE ---" << std::endl;

            const auto& liste = utenteLoggato->getListePermesse();

            if (liste.empty()) {
                std::cout << "(Nessuna lista associata. Creane una!)" << std::endl;
            } else {
                for (const auto& nome : liste) {
                    std::cout << "- " << nome << std::endl;
                }
            }
            std::cout << "--------------------" << std::endl;
            std::cout << "1. Apri una Lista esistente" << std::endl;
            std::cout << "2. Crea una Nuova Lista" << std::endl;
            std::cout << "3. Scollegati da una Lista (Lascia la lista agli altri)" << std::endl;
            std::cout << "4. Elimina Lista definitivamente (Per tutti!)" << std::endl;
            std::cout << "5. ELIMINA IL TUO ACCOUNT" << std::endl;
            std::cout << "0. Logout" << std::endl;
            std::cout << "> Scelta: ";

            int sceltaMenù;
            std::cin >> sceltaMenù;

            // Torna al menù principale
            if (sceltaMenù == 0) {
                utenteLoggato = nullptr;
            }
            // --- CREAZIONE NUOVA LISTA ---
            else if (sceltaMenù == 2) {
                std::string nomeLista;
                std::cout << "Nome del file (es. 'spesa_casa.txt'): ";
                std::cin >> nomeLista;
                ListaSpesa nuova(nomeLista);
                nuova.salvaSuFile(nomeLista);
                utenteLoggato->aggiungiListaPermessa(nomeLista);
                Utente::salvaUtenti("utenti.txt", databaseUtenti);
                std::cout << "Lista creata con successo.\n";
                pausa();
            }
            // --- SCOLLEGAMENTO ---
            else if (sceltaMenù == 3) {
                std::string nomeDaRimuovere;
                std::cout << "Inserisci il nome della lista da cui vuoi scollegarti: ";
                std::cin >> nomeDaRimuovere;

                // Controllo se l'utente ha davvero questa lista
                bool possiedeLista = false;
                for(const auto& nome : liste) {
                    if(nome == nomeDaRimuovere)
                        possiedeLista = true;
                }

                if(possiedeLista) {
                    utenteLoggato->rimuoviListaPermessa(nomeDaRimuovere);
                    Utente::salvaUtenti("utenti.txt", databaseUtenti);
                    std::cout << "Ti sei scollegato dalla lista correttamente.\n";
                } else {
                    std::cout << "Errore: Non sei collegato a questa lista.\n";
                }
                pausa();
            }
            // --- ELIMINAZIONE LISTA (per tutti) ---
            else if (sceltaMenù == 4) {
                std::string nomeDaCancellare;
                std::cout << "ATTENZIONE: Questo eliminera' il file per TUTTI gli utenti.\n";
                std::cout << "Inserisci il nome del file da eliminare definitivamente: ";
                std::cin >> nomeDaCancellare;

                // Controllo se l'utente ha i permessi per agire su questa lista
                bool possiedeLista = false;
                for(const auto& nome : liste) {
                    if(nome == nomeDaCancellare)
                        possiedeLista = true;
                }
                if(possiedeLista) {
                    // Cancello il file per tutti gli utenti
                    if (std::remove(nomeDaCancellare.c_str()) == 0) {
                        for (auto* u : databaseUtenti) {
                            u->rimuoviListaPermessa(nomeDaCancellare);
                        }
                        Utente::salvaUtenti("utenti.txt", databaseUtenti);
                        std::cout << "Lista eliminata definitivamente per tutti.\n";
                    } else {
                        std::cout << "Errore: Impossibile eliminare il file (potrebbe non esistere).\n";
                    }
                } else {
                    std::cout << "Errore: Non possiedi una lista con questo nome.\n";
                }
                pausa();
            }
            // --- ELIMINAZIONE ACCOUNT UTENTE ---
            else if (sceltaMenù == 5) {
                char conferma;
                std::cout << "ATTENZIONE: Stai per eliminare il tuo account: " << utenteLoggato->getNickname() << ".\n";
                std::cout << "L'operazione e' irreversibile. Sei sicuro? (s/n): ";
                std::cin >> conferma;

                if (conferma == 's' or conferma == 'S') {
                    databaseUtenti.remove(utenteLoggato);
                    Utente::salvaUtenti("utenti.txt", databaseUtenti);
                    delete utenteLoggato;
                    utenteLoggato = nullptr; // Questo mi riporta al Login
                    std::cout << "Account eliminato con successo. Arrivederci!\n";
                    pausa();
                } else {
                    std::cout << "Operazione annullata.\n";
                    pausa();
                }
            }
            // --- APRO UNA LISTA ESISTENTE ---
            else if (sceltaMenù == 1) {
                std::string nomeTarget;
                std::cout << "Inserisci il nome del file da aprire: ";
                std::cin >> nomeTarget;
                bool permesso = false;
                for(const auto& nome : liste) {
                    if(nome == nomeTarget)
                        permesso = true;
                }
                if (permesso) {
                    // =========================================================
                    // DENTRO LA LISTA (Gestione Prodotti)
                    // =========================================================

                    ListaSpesa* listaCorrente = new ListaSpesa(nomeTarget);
                    listaCorrente->caricaDaFile(nomeTarget);

                    // --- OBSERVER ---
                    // Verifico quali utenti hanno accesso alla lista e li aggiungo come observer
                    for (auto* u : databaseUtenti) {
                        if (u != utenteLoggato) {
                            bool condivideLista = false;
                            for (const auto& file : u->getListePermesse()) {
                                if (file == nomeTarget) {
                                    condivideLista = true;
                                    break;
                                }
                            }
                            if (condivideLista) {
                                listaCorrente->aggiungiObserver(u);
                            }
                        }
                    }

                    bool inLista = true;
                    while(inLista) {
                        Grafica::pulisciSchermo();
                        std::cout << "LISTA APERTA: " << listaCorrente->getNomeListaSpesa() << std::endl;
                        std::cout << "1. Aggiungi Prodotto" << std::endl;
                        std::cout << "2. Rimuovi Prodotto" << std::endl;
                        std::cout << "3. Visualizza Resoconto" << std::endl;
                        std::cout << "4. Condividi Lista con un amico" << std::endl;
                        std::cout << "0. Indietro (Torna alla Dashboard)" << std::endl;
                        std::cout << "> Scelta: ";

                        int sc;
                        std::cin >> sc;

                        if (sc == 0) {
                            inLista = false;
                        }
                        // --- AGGIUNGI PRODOTTO ---
                        else if (sc == 1) {
                            std::string n, m, c; int q; float p;
                            std::cin.ignore();

                            std::cout << "Nome: "; std::getline(std::cin, n);
                            std::cout << "Marca: "; std::getline(std::cin, m);
                            std::cout << "Categoria: "; std::getline(std::cin, c);
                            std::cout << "Quantita': "; std::cin >> q;
                            std::cout << "Prezzo: "; std::cin >> p;

                            Prodotto nuovoP(n, m, c, q, p);

                            if (listaCorrente->aggiungiProdotto(nuovoP)) {
                                std::cout << "Prodotto aggiunto.\n";
                            } else {
                                std::cout << "Errore: Prodotto gia' presente!\n";
                            }
                            pausa();
                        }
                        // --- RIMOZIONE PRODOTTO ---
                        else if (sc == 2) {
                            std::cout << "Inserisci il numero del prodotto da eliminare (1 per il primo, ecc): ";
                            int i;
                            std::cin >> i;

                            if (listaCorrente->rimuoviProdotto(i - 1)) {
                                std::cout << "Prodotto rimosso.\n";
                            } else {
                                std::cout << "Indice non valido.\n";
                            }
                            pausa();
                        }
                        // --- RESOCONTO ---
                        else if (sc == 3) {
                            Grafica::stampaResoconto(*listaCorrente);
                        }
                        // --- CONDIVISIONE LISTA ---
                        else if (sc == 4) {
                            std::string amico;
                            std::cout << "Nickname dell'utente con cui condividere: ";
                            std::cin >> amico;

                            bool trovatoAmico = false;

                            for(auto* u : databaseUtenti) {
                                if(u->getNickname() == amico) {
                                    trovatoAmico = true;

                                    // Controllo se l'amico ha già la lista
                                    bool giaCondivisa = false;
                                    for(const auto& filePosseduto : u->getListePermesse()) {
                                        if (filePosseduto == nomeTarget) {
                                            giaCondivisa = true;
                                            break;
                                        }
                                    }
                                    // Se non ce l'ha gliela condivido
                                    if (!giaCondivisa) {
                                        u->aggiungiListaPermessa(nomeTarget);
                                        Utente::salvaUtenti("utenti.txt", databaseUtenti);
                                        std::cout << "Lista condivisa con " << amico << "!\n";
                                    } else {
                                        // Se ce l'ha già, avviso l'utente
                                        std::cout << "Attenzione: L'utente " << amico << " vede gia' questa lista!\n";
                                    }
                                    break;
                                }
                            }

                            if(!trovatoAmico) {
                                std::cout << "Utente non trovato nel database.\n";
                            }
                            pausa();
                        }
                    }

                    // Salvo le modifiche sul file e libero la memoria
                    listaCorrente->salvaSuFile(nomeTarget);
                    delete listaCorrente;

                } else {
                    std::cout << "Accesso negato: Non hai i permessi per questa lista.\n";
                    pausa();
                }
            }
        }
    }

    // Libero la memoria di tutti gli utenti prima di chiudere
    for (auto* u : databaseUtenti) {
        delete u;
    }

    std::cout << "Programma terminato correttamente.\n";
    return 0;
}