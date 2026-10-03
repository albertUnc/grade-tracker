from platformdirs import user_data_dir
from pathlib import Path
import json
import settings
import sys
import statistics
from enum import Enum

def validateArgs() -> None:
    if len(sys.argv) < settings.MIN_ARGS:
        sys.exit("Not enough arguments!")
    if sys.argv[1] not in settings.commands: sys.exit("Invalid command!")

def load_grades() -> dict:
    app_data = Path(user_data_dir(settings.APP_NAME))
    with open(app_data/settings.DATA_JSON_FILE_NAME, "r") as file:
        contents = file.read()
    if not contents.strip():
        return {}
    temp: dict = json.loads(contents)
    return temp
def save_grades(grades: dict) -> None:
    app_data = Path(user_data_dir(settings.APP_NAME))
    with open(app_data/settings.DATA_JSON_FILE_NAME, "w") as file:
        json.dump(grades, file, indent=settings.JSON_INDENTATION_SPACES)

def add_grade(subj: str, grade: int) -> None:
    grades=load_grades()
    grades.setdefault(subj, []).append(grade)
    save_grades(grades)

def remove_grade(subj: str, grade: int) -> None:
    grades=load_grades()
    category = grades.get(subj)
    if category == None:
        sys.exit("Subject doesn't exist.")
    if grade not in category:
        sys.exit("No grade like that in that subject.")
    category.remove(grade)
    save_grades(grades)

def remove_subject(subj: str) -> None:
    grades=load_grades()
    if grades.get(subj) == None: return
    del grades[subj]
    save_grades(grades)

def print_grades() -> None:
    grades = load_grades()
    for subj, grade_list in grades.items():
        for grade in grade_list:
            formatted_subj = subj.ljust(15)
            print(f"Subject: {formatted_subj} Grade: {grade}")
        print()

def show_averages() -> None:
    subjects = load_grades()
    grades:list = [grade for subj in subjects for grade in subj]
    grades_avg = statistics.mean(grades)
    subjects_avgs = [statistics.mean(grades) for grades in subjects.values()]
    subjects_avg = statistics.mean(subjects_avgs)

    print("Your average in each subject:")
    for i, subj in enumerate(subjects):
        print(f"{subj}: {subjects_avgs[i]}")
    print(f"Your average based on all grades: {grades_avg}")
    print(f"Your average based on subjects' averages: {subjects_avg}")

def effect() -> None:
    args = sys.argv
    command = args[1]
    if command == "average" or command == "averages": 
        show_averages()
        return
    if command == "list":
        print_grades()
        return

    class Action(Enum):
        Add = "add"
        Remove = "remove"
    class Target(Enum):
        Subject = "subject"
        Grade = "grade"
    action: Action = None
    target: Target = Target(command)
    if args[2] not in ("add", "remove"):
        sys.exit(f"Argument \"{args[2]}\" is invalid!")
    else: action = Action(args[2])

    match action:
        case Action.Add:
            if target == Target.Subject:
                sys.exit("Adding a subject is invalid. Add a new grade to the new subject to automatically add it.")
            else:
                add_grade(args[3], int(args[4]))
        case Action.Remove:
            if target == Target.Subject:
                remove_subject(args[3])
            else:
                remove_grade(args[3], int(args[4]))


def main() -> str:
    validateArgs()
    effect()

if __name__ == "__main__": main()