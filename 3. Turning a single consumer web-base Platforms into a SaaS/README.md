# Turning a single consumer web-based Platforms into a SaaS
A web-based gaming platform (=gPlatform) is currently providing it’s services to one single gaming site (=gSite).
The services provided by gPlatform to gSite include hosting web-games and backoffice for managing players that sign-up and play on gSite.

We want to make gPlatform into a SaaS that can be sold to other gaming sites as subscription-based service.

Each new gaming company operating a gaming site, will have it’s own dedicated domain - for example:
Company A will have a domain cool-games.com
Company B will have a domain luck-games.co.uk 
etc

Currently at gPlatform, users are identified by using email as a unique key. 

## Give a short, clear explanation for every question below:

1. How can we design the system in a way that every Company will be able to serve games on their gaming site from their domain?
To allow each company to serve games on their own domain, we need to implement a multi-tenancy architecture. This includes isolating the data and funcitons for each company while sharing the same infrastructure. This can be achieved using concepts such as subdomains or custom domains for each company. When a request comes from a specific domain, the system will route it to that tenant's data and services.
2. What modification should be done to the users table at gPlatform to support this change?
To support multiple companies, we need to modify gPlatform's Users table to include a new column for the tenant ID. This column will help in associating each user with the specific company they belong to. Additionally, we may need to adjust the unique key constraint to include a combination of email and company ID to ensure uniqueness across tenants.
3. Considering we have 1 backend cluster that serves all companies, how can we validate a user login on one gaming domain in such a way that it does not give access to a different gaming domain? (i.e. authenticating on site A, grants access to site A only)
To validate a user login on one gaming domain without granting access to others, we need to implement a mechanism like token based authentication. When a user logs in, the system can issue a unique token that is tied to the user's session and the specific domain they are accessing. This token must be validated on subsequent requests to ensure that the user can only access resources in the domain they are logged in from. By including the domain information in the token and verifying it with each request, we can maintain the isolation between different gaming domains.
