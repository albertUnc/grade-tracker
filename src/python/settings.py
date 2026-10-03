APP_NAME: str = "grade-tracker"
DATA_JSON_FILE_NAME:str = "grades.json"
MIN_ARGS: int = 2 # If set to anything smaller than 1 will stop the program every time
JSON_INDENTATION_SPACES: int = 4

commands: list = [ # command name
    "average",
    "averages",
    "list",
    "subject",
    "grade",
]
