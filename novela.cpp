#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <cstring>

using namespace std;

// Função para matar um processo
void matar(pid_t pid, string quem, string alvo) {
    if (kill(pid, SIGKILL) == 0) {
        cout << quem << " matou " << alvo << " (PID: " << pid << ")" << endl;
    } else {
        perror(("Erro ao tentar " + quem + " matar " + alvo).c_str());
    }
}

// Função de vida de cada processo
void viver(string nome, pid_t pai_pid,
           int tempo_matar_alvo = -1, pid_t pid_alvo = -1,
           int tempo_suicidio = -1) {
    
    int idade = 0;
    pid_t meu_pid = getpid();
    pid_t meu_pai = getppid();

    while (true) {
        sleep(1);
        idade++;

        // Imprime situação atual
        cout << "Nome: " << nome
             << " | Idade: " << idade
             << " | PID: " << meu_pid
             << " | PPID: " << getppid() << endl;

        // Mata alvo, se tiver ordem programada
        if (tempo_matar_alvo != -1 && idade == tempo_matar_alvo) {
            matar(pid_alvo, nome, "alvo");
        }

        // Suicídio, se programado
        if (tempo_suicidio != -1 && idade == tempo_suicidio) {
            cout << nome << " (PID: " << meu_pid << ") se suicidou." << endl;
            exit(0);
        }
    }
}

int main() {
    pid_t pid_filho1 = -1;
    pid_t pid_filho2 = -1;
    pid_t pid_neto1 = -1;
    pid_t pid_neto2 = -1;

    int idade_pai = 0;
    pid_t pid_pai = getpid();

    cout << "Pai nasceu (PID: " << pid_pai << ")" << endl;

    while (true) {
        sleep(1);
        idade_pai++;

        cout << "Nome: Pai"
             << " | Idade: " << idade_pai
             << " | PID: " << getpid()
             << " | PPID: " << getppid() << endl;

        // Aos 10 segundos, cria Filho1
        if (idade_pai == 10) {
            pid_filho1 = fork();
            if (pid_filho1 == 0) {
                // Processo Filho1
                int idade = 0;
                pid_neto1 = -1;

                while (true) {
                    sleep(1);
                    idade++;

                    cout << "Nome: Filho1"
                         << " | Idade: " << idade
                         << " | PID: " << getpid()
                         << " | PPID: " << getppid() << endl;

                    // Cria Neto1 após 15 segundos
                    if (idade == 15) {
                        pid_neto1 = fork();
                        if (pid_neto1 == 0) {
                            // Processo Neto1
                            viver("Neto1", getppid());
                        } else {
                            cout << "Neto1 nasceu (PID: " << pid_neto1 << ")" << endl;
                        }
                    }

                    // Aos 50 segundos mata o Pai
                    if (idade == 50) {
                        matar(pid_pai, "Filho1", "Pai");
                    }

                    // Aos 55 segundos mata Neto1 (se existir)
                    if (idade == 55 && pid_neto1 > 0) {
                        matar(pid_neto1, "Filho1", "Neto1");
                    }

                    // Aos 57 se suicida
                    if (idade == 57) {
                        cout << "Filho1 (PID: " << getpid() << ") se suicidou." << endl;
                        exit(0);
                    }
                }
            } else {
                cout << "Filho1 nasceu (PID: " << pid_filho1 << ")" << endl;
            }
        }

        // Aos 20 segundos, cria Filho2
        if (idade_pai == 20) {
            pid_filho2 = fork();
            if (pid_filho2 == 0) {
                // Processo Filho2
                int idade = 0;
                pid_neto2 = -1;

                while (true) {
                    sleep(1);
                    idade++;

                    cout << "Nome: Filho2"
                         << " | Idade: " << idade
                         << " | PID: " << getpid()
                         << " | PPID: " << getppid() << endl;

                    // Cria Neto2 após 15 segundos
                    if (idade == 15) {
                        pid_neto2 = fork();
                        if (pid_neto2 == 0) {
                            // Processo Neto2
                            viver("Neto2", getppid(),
                                  60, getppid(), // Aos 60 mata Filho2
                                  63);           // Aos 63 se suicida
                        } else {
                            cout << "Neto2 nasceu (PID: " << pid_neto2 << ")" << endl;
                        }
                    }
                }
            } else {
                cout << "Filho2 nasceu (PID: " << pid_filho2 << ")" << endl;
            }
        }
    }

    return 0;
}
