<?php

namespace App\Http\Controllers;

use App\Models\Painting;
use Illuminate\Http\Request;
use App\Models\Author;
use App\Models\Museum;

class PaintingController extends Controller
{
    /**
     * Display a listing of the resource.
     *
     * @return \Illuminate\Http\Response
     */
    public function index()
    {
        $paintings = Painting::latest()->get();

        return view('paintings.index', compact('paintings'));
    }

    /**
     * Show the form for creating a new resource.
     *
     * @return \Illuminate\Http\Response
     */
    public function create()
    {
        return view('paintings.create');
    }

    /**
     * Store a newly created resource in storage.
     *
     * @param  \Illuminate\Http\Request  $request
     * @return \Illuminate\Http\Response
     */
    public function store(Request $request)
    {
        $attrs = request()->validate([
            'author' => 'required|exists:authors,name',
            'museum' => 'required|exists:museums,name',
            'title' => 'required',
            'description' => 'max:255',
            'year' => 'required'

        ]);

        $author = Author::where('name', request('author'))->first();
        $museum = Museum::where('name', request('museum'))->first();

        Painting::create([
            'author_id' => $author->id,
            'museum_id' => $museum->id,
            'title' => $attrs['title'],
            'description' => $attrs['description'],
            'year_of_production' => $attrs['year']
        ]);

        return redirect('/paintings');
    }

    /**
     * Display the specified resource.
     *
     * @param  \App\Models\Painting  $painting
     * @return \Illuminate\Http\Response
     */
    public function show(Painting $painting)
    {
        return view('paintings.show', compact('painting'));
    }

    /**
     * Show the form for editing the specified resource.
     *
     * @param  \App\Models\Painting  $painting
     * @return \Illuminate\Http\Response
     */
    public function edit(Painting $painting)
    {
        //
    }

    /**
     * Update the specified resource in storage.
     *
     * @param  \Illuminate\Http\Request  $request
     * @param  \App\Models\Painting  $painting
     * @return \Illuminate\Http\Response
     */
    public function update(Request $request, Painting $painting)
    {
        //
    }

    /**
     * Remove the specified resource from storage.
     *
     * @param  \App\Models\Painting  $painting
     * @return \Illuminate\Http\Response
     */
    public function destroy(Painting $painting)
    {
        //
    }
}
