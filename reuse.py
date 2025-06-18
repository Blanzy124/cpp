import json

def validatedJson(j):
  try:
    json.loads(j)
    return True
  except (json.JSONDecodeError, TypeError):
    return False