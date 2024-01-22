type BodyType =
  | string
  | Blob
  | BufferSource
  | FormData
  | URLSearchParams
  | ReadableStream<Uint8Array>
  | null;

class HttpClient {
  private baseUrl: string;

  constructor(baseUrl: string) {
    this.baseUrl = baseUrl;
  }

  private async handleResponse(response: Response) {
    if (!response.ok) {
      return response;
    }

    return await response.json();
  }

  async get(
    endpoint: string,
    headersConfig: HeadersInit = { 'Content-Type': 'application/json' },
  ) {
    const url = `${this.baseUrl}/${endpoint}`;
    const response = await fetch(url, {
      method: 'GET',
      headers: headersConfig,
    });

    return this.handleResponse(response);
  }

  async post(
    endpoint: string,
    data: BodyType,
    headersConfig: HeadersInit = { 'Content-Type': 'application/json' },
  ) {
    const url = `${this.baseUrl}/${endpoint}`;
    const response = await fetch(url, {
      method: 'POST',
      headers: headersConfig,
      body: data,
    });

    return this.handleResponse(response);
  }

  async put(
    endpoint: string,
    data: BodyType,
    headersConfig: HeadersInit = { 'Content-Type': 'application/json' },
  ) {
    const url = `${this.baseUrl}/${endpoint}`;
    const response = await fetch(url, {
      method: 'PUT',
      headers: headersConfig,
      body: data,
    });

    return this.handleResponse(response);
  }

  async delete(
    endpoint: string,
    data: BodyType,
    headersConfig: HeadersInit = { 'Content-Type': 'application/json' },
  ) {
    const url = `${this.baseUrl}/${endpoint}`;
    const response = await fetch(url, {
      method: 'DELETE',
      headers: headersConfig,
      body: data,
    });

    return this.handleResponse(response);
  }
}

const HttpClientIngress = new HttpClient(
  `http://${process.env.ingressHost}:${process.env.ingressPort}`,
);

export default HttpClientIngress;
