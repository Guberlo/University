@extends('layout')

@section('content')
    
							<!-- Section -->
                            <section>
                                <header class="major">
                                    <h2>Get a look at all of our books</h2>
                                </header>
                                <div class="posts">
                                    @foreach ($books as $book)
                                    <article>
                                        <a href="/library/{{$book->id}}" class="image"><img src="/images/pic01.jpg" alt="" /></a>
                                        <h3>{{$book->title}}</h3>
                                        <p>{{$book->description}}</p>
                                        <ul class="actions">
                                            <li><a href="/library/{{$book->id}}" class="button">More</a></li>
                                        </ul>
                                    </article>
                                    @endforeach
                                </div>
                            </section>

                    </div>
                    <div class="col-12">
                    <ul class="pagination">
                        {{ $books->links() }}
                    </ul>
                    </div>
                </div>
@endsection