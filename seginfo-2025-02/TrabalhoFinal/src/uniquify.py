import os

# Source - https://stackoverflow.com/a
# Posted by starikcetin
# Retrieved 2025-11-15, License - CC BY-SA 4.0

def uniquify(path: str) -> str:
    filename, extension = os.path.splitext(path)
    counter = 1

    while os.path.exists(path):
        path = filename + " (" + str(counter) + ")" + extension
        counter += 1

    return path