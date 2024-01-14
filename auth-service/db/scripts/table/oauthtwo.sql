DROP TABLE IF EXISTS oauthtwo;

CREATE TABLE oauthtwo
(
  /* ID fields */
  id BIGSERIAL,
  provider_id BIGINT,

  /* Mandatory fields */
  refresh_token TEXT,	-- JWT token refresh_token provider

  /* Optional fields */

  /* Primary keys Constraints */
  CONSTRAINT oauthtwo_pkey PRIMARY KEY (id),

  /* Foreign keys Constraints */

  CONSTRAINT oauthtwo_provider FOREIGN KEY (provider_id)
  REFERENCES provider (id)

/* Unique Constraints */
);

/* For one-to-one relation ship */
