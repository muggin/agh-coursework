ImagePath = "/Users/Wojtek/Pictures/Moje zdjecia/palec.JPG".
Method = post.
Url = "https://api.imgur.com/3/upload".
Headers = [{"Authorization", "Client-ID ca1c42ef1d2fb95"}].
ContentType = "image/jpg".
{ok, Binary} = file:read_file(Filename).
Body = base64:encode(Binary).
HttpOptions = [{ssl, [{verify, 0}]}].

httpc:request(Method, {Url, Headers, ContentType, Body}, HttpOptions, []).