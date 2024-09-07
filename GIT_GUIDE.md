# Git-Leitfaden 

## Grundlagen

Git ist ein Versionskontrollsystem, das es uns ermöglicht, den Verlauf unserer Projektdateien zu verfolgen und Änderungen zu verwalten. Hier sind einige grundlegende Befehle:

- `git init`: Initialisiert ein neues Git-Repository
- `git clone [URL]`: Klont ein Repository von GitHub
- `git add [Dateiname]`: Fügt Änderungen zum Staging-Bereich hinzu
- `git commit -m "Nachricht"`: Speichert die Änderungen mit einer Nachricht
- `git push origin [Branch-Name]`: Überträgt Änderungen auf den Remote-Server
- `git pull origin [Branch-Name]`: Holt die neuesten Änderungen vom Remote-Server

## Branching und Merging

- **Branch erstellen**: `git checkout -b [Branch-Name]`
- **Branch wechseln**: `git checkout [Branch-Name]`
- **Branch mergen**: `git merge [Branch-Name]`
- **Konflikte lösen**: Bei Merge-Konflikten manuell beheben und dann `git add` und `git commit` verwenden

## Arbeitsablauf

1. **Branch erstellen**: Erstelle einen neuen Branch für jede neue Funktion oder Bugfix.
2. **Änderungen committen**: Stelle sicher, dass du häufig committest und sinnvolle Nachrichten verwendest.
3. **Pull Request erstellen**: Reiche einen Pull Request ein, um deine Änderungen zu integrieren.
4. **Code-Review**: Alle Änderungen sollten vor dem Mergen von mindestens einem Teammitglied überprüft werden.

## Commit-Nachrichten

Verwende klare und prägnante Commit-Nachrichten. Beispiele:

- `Fix bug in user login`
- `Add new feature for report generation`
- `Refactor authentication module`

## Best Practices

- **Regelmäßig committen**: Vermeide große Commits und committe häufig.
- **Gute Branch-Namen**: Verwende beschreibende Namen für Branches, z.B. `feature/login-page` oder `bugfix/issue-123`.
- **Keine sensiblen Daten**: Stelle sicher, dass keine sensiblen Daten wie Passwörter in das Repository gelangen.

## Ressourcen

- [Git-Dokumentation](https://git-scm.com/doc)
- [GitHub Hilfe](https://docs.github.com/en/github)

