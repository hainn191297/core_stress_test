# LogManager Component

Log component with ElasticSearch: https://www.elastic.co/

## 1. Install

- Quick start:  https://www.elastic.co/start
- Elastic: http://elastic.wala.vn
- Kibana: https://vt2-elk.wala.vn
- Account: TODO:

## 2. Requirement KPI

- Total registered user, updated every 15s
- Active user per day (average by day, by week, by month)
- Statistic on registered user (by Telco, by device, by OS, by Region, by Age, etc)
- New user per day
- Total msg/day/week/year
- Total call/day/week/year
- Statistic msg by type
- Total SMS Out /day/week/month

## 3. KPI query

To perform query, login to Kibana, go to tab 'Dev Tools'
For more info about syntax query, refer to document : https://www.elastic.co/guide/en/elasticsearch/reference/current/docs.html

### 1. Statistic Message

Message has 2 type: SMSOUT message & NORMAL(photo, sticker ...) message

- Get total message
```
  GET /message/_count
  {
    "query": { "match_all": {} }
  }
```
- Get total message with type `smsout` or `normal`
```
  GET /message/_count
  {
    "query": {
      "term": { "type": "smsout" }
    }
  }
```
- Get total message in range of time in miliseconds(10 digit from epoll time). See http://www.epochconverter.com/
```
  GET /message/_search
  {
    "query": {
      "bool": {
        "filter": [
          {"range": {"time_t" : { "gte": "xxx", "lt": "yyy"}}}
        ]
      }
    },
    "size": 0
  }
```
- Get total message with `type` in range of time in miliseconds(10 digit from epoll time)
```
  GET /message/_search
  {
    "query": {
      "bool": {
        "must": [
          {"match": {"type": "smsout"}}
        ],
        "filter": [
          {"range": {"time_t" : { "gte": "xxx", "lt": "yyy"}}}
        ]
      }
    },
    "size": 0
  }
```
### 2. Statistic Register User

- Get total user registered
```
  GET /user/register/_count
  {
    "query": { "match_all": {} }
  }
```
- Get total register user in range of time in miliseconds(10 digit from epoll time)
```
  GET /user/register/_search
  {
    "query": {
      "bool": {
        "filter": [
          {"range": {"time_t" : { "gte": "xxx", "lt": "yyy"}}}
        ]
      }
    },
    "size": 0
  }
```
- Get total register user by telco(viettel, vinaphone, mobiphone ...)
```
  GET /user/register/_search
  {
    "query": {
      "bool": {
        "must": [
          {"match": {"telco": "viettel"}}
        ]
      }
    },
    "size": 0
  }
```
### 3. Statistic Login User

- Get active user in range of time in miliseconds(10 digit from epoll time)
```
  GET /user/login/_search
  {
    "query": {
      "bool": {
        "must": [
          {"match": {"type": "login"}}
        ],
        "filter": [
          {"range": {"time_t" : { "gte": "1479348052", "lt": "now"}}}
        ]
      }
    },
    "aggs": {
      "active_user": {"cardinality": { "field": "id" }}
    },
    "size": 0
  }
```
- Note of have error: elastich search Set fielddata=true on [color] in order to load fielddata.See more at https://www.elastic.co/guide/en/elasticsearch/reference/current/fielddata.html
```
  PUT user/_mapping/login
  {
    "properties": {
      "id": {
        "type": "text",
        "fielddata": true
      },
      "time_t": {
        "type": "text",
        "fielddata": true
      }
    }
  }
```
- Retrive some most active user in range of time in miliseconds(10 digit from epoll time)
```
  GET /user/login/_search
  {
    "query": {
      "bool": {
        "must": [
          {"match": {"type": "login"}}
        ],
        "filter": [
          {"range": {"time_t" : { "gte": "1479348052", "lt": "now"}}}
        ]
      }
    },
    "aggs": {
      "most_active_user": {"terms": { "field": "id" }}
    },
    "size": 0
  }
```


## 4. Stuff Markdown

 * [Markdown Editor](https://jbt.github.io/markdown-editor/)
 * [markdown-it](https://github.com/markdown-it/markdown-it) for Markdown parsing
 * [CodeMirror](http://codemirror.net/) for the awesome syntax-highlighted editor
 * [highlight.js](http://softwaremaniacs.org/soft/highlight/en/) for syntax highlighting in output code blocks
 * [js-deflate](https://github.com/dankogai/js-deflate) for gzipping of data to make it fit in URLs
