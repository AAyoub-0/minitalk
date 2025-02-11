#!/bin/bash

# Vérification des arguments
if [ "$#" -ne 3 ]; then
    echo "Usage: $0 <pid> <message> <nombre d'exécutions>"
    exit 1
fi

PID=$1
MESSAGE=$2
COUNT=$3

# Vérification que le PID est un entier
if ! [[ "$PID" =~ ^[0-9]+$ ]]; then
    echo "Erreur : Le PID doit être un nombre entier."
    exit 1
fi

# Vérification que le nombre d'exécutions est un entier
if ! [[ "$COUNT" =~ ^[0-9]+$ ]]; then
    echo "Erreur : Le nombre d'exécutions doit être un nombre entier."
    exit 1
fi

# Boucle d'exécution du client
for ((i = 0; i < COUNT; i++)); do
    echo "Envoi du message : '$MESSAGE' à PID $PID (itération $((i + 1))/$COUNT)"
    ./client "$PID" "$MESSAGE"
    sleep 0.5  # Pause de 500ms
done

echo "Test terminé."
